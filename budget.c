#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

Budget budgets[MAX_DEPTS];
int deptCount = 0;

/* Remaining budget = allocated - spent (negative means overspent). */
double calculateBudget(double allocated, double spent)
{
    return allocated - spent;
}

const char *budgetStatus(double remaining)
{
    if (remaining >= 0) {
        return "WITHIN BUDGET";
    }
    return "EXCEEDED";
}

/* Returns the index of the department (ignoring upper/lower case), or -1. */
int findBudgetByName(const char *name)
{
    for (int i = 0; i < deptCount; i++) {
        if (equalsIgnoreCase(budgets[i].deptName, name)) {
            return i;
        }
    }
    return -1;
}

void addBudget(void)
{
    Budget b;

    if (deptCount >= MAX_DEPTS) {
        printf("Department list is full (maximum %d).\n", MAX_DEPTS);
        return;
    }

    printf("\n--- Add Department Budget ---\n");

    for (;;) {
        readNonEmpty("Enter Department: ", b.deptName, sizeof b.deptName);
        if (findBudgetByName(b.deptName) == -1) {
            break;
        }
        printf("That department already has a budget. Use 'Record Expenditure' to add spending.\n");
    }

    for (;;) {
        b.allocated = readMoney("Enter Allocated Budget (N$): ");
        if (b.allocated > 0) {
            break;
        }
        printf("Allocated budget must be greater than zero.\n");
    }
    b.spent = readMoney("Enter Expenditure so far (N$): ");

    budgets[deptCount++] = b;
    printf("Budget added. Remaining: N$%.2f - %s\n",
           calculateBudget(b.allocated, b.spent),
           budgetStatus(calculateBudget(b.allocated, b.spent)));
}

void recordExpenditure(void)
{
    char name[DEPT_NAME_LEN];

    if (deptCount == 0) {
        printf("No department budgets registered yet.\n");
        return;
    }

    readNonEmpty("Enter Department: ", name, sizeof name);
    int index = findBudgetByName(name);
    if (index == -1) {
        printf("Department not found.\n");
        return;
    }

    double amount = readMoney("Enter additional expenditure (N$): ");
    budgets[index].spent += amount;

    double remaining = calculateBudget(budgets[index].allocated, budgets[index].spent);
    printf("%s: spent N$%.2f, remaining N$%.2f - %s\n",
           budgets[index].deptName, budgets[index].spent, remaining, budgetStatus(remaining));
}

void displayBudgets(void)
{
    if (deptCount == 0) {
        printf("No department budgets registered yet.\n");
        return;
    }

    printf("\n%-20s %15s %15s %15s  %s\n", "Department", "Allocated", "Spent", "Remaining", "Status");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < deptCount; i++) {
        double remaining = calculateBudget(budgets[i].allocated, budgets[i].spent);
        printf("%-20.20s %15.2f %15.2f %15.2f  %s\n",
               budgets[i].deptName, budgets[i].allocated, budgets[i].spent,
               remaining, budgetStatus(remaining));
    }
}

void showExceededBudgets(void)
{
    int count = 0;

    for (int i = 0; i < deptCount; i++) {
        double remaining = calculateBudget(budgets[i].allocated, budgets[i].spent);
        if (remaining < 0) {
            printf("%s exceeded its budget by N$%.2f\n", budgets[i].deptName, -remaining);
            count++;
        }
    }
    if (count == 0) {
        printf("No department has exceeded its budget.\n");
    }
}

void budgetManagement(void)
{
    int choice;

    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add Department Budget\n2. Record Expenditure\n3. Display Budgets\n");
        printf("4. Show Departments Over Budget\n5. Back\n");
        choice = readMenuChoice("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addBudget();            break;
            case 2: recordExpenditure();    break;
            case 3: displayBudgets();       break;
            case 4: showExceededBudgets();  break;
            default: break;
        }
    } while (choice != 5);
}
