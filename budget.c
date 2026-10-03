
#include <stdio.h>
#include <string.h>
#include "budget.h"

#define MAX_BUDGETS 50

typedef struct {
    char department[50];
    float budget;
    float expenditure;
} Budget;

void addBudget(Budget budgets[], int *count);
void addExpenditure(Budget budgets[], int count);
void displayBudgets(Budget budgets[], int count);
void showOverBudget(Budget budgets[], int count);



void addBudget(Budget budgets[], int *count)
{
    if (*count >= MAX_BUDGETS) {
        printf("Budget list is full.\n");
        return;
    }

    printf("\nEnter department name: ");
    scanf("%49s", budgets[*count].department);

    do {
        printf("Enter budget: N$");
        scanf("%f", &budgets[*count].budget);

        if (budgets[*count].budget < 0)
            printf("Budget cannot be negative.\n");

    } while (budgets[*count].budget < 0);

    budgets[*count].expenditure = 0;

    (*count)++;

    printf("Budget added successfully.\n");
}


void addExpenditure(Budget budgets[], int count)
{
    char name[50];
    float amount;
    int i;

    if (count == 0) {
        printf("\nNo budgets available.\n");
        return;
    }

    printf("\nEnter department name: ");
    scanf("%49s", name);

    for (i = 0; i < count; i++) {

        if (strcmp(budgets[i].department, name) == 0) {

            do {
                printf("Enter expenditure: N$");
                scanf("%f", &amount);

                if (amount < 0)
                    printf("Expenditure cannot be negative.\n");

            } while (amount < 0);

            budgets[i].expenditure += amount;

            printf("Expenditure added successfully.\n");

            if (budgets[i].expenditure > budgets[i].budget)
                printf("Status: OVER BUDGET\n");
            else
                printf("Status: WITHIN BUDGET\n");

            return;
        }
    }

    printf("Department not found.\n");
}


void displayBudgets(Budget budgets[], int count)
{
    int i;
    float remaining;

    printf("\n--- Budget Overview ---\n");

    if (count == 0) {
        printf("No budgets available.\n");
        return;
    }

    for (i = 0; i < count; i++) {

        remaining = budgets[i].budget - budgets[i].expenditure;

        printf("\nDepartment: %s\n", budgets[i].department);
        printf("Budget:      N$%.2f\n", budgets[i].budget);
        printf("Expenditure: N$%.2f\n", budgets[i].expenditure);
        printf("Remaining:   N$%.2f\n", remaining);

        if (budgets[i].expenditure > budgets[i].budget)
            printf("Status: OVER BUDGET\n");
        else
            printf("Status: WITHIN BUDGET\n");
    }
}


void showOverBudget(Budget budgets[], int count)
{
    int i;
    int found = 0;

    printf("\n--- Departments Over Budget ---\n");

    for (i = 0; i < count; i++) {

        if (budgets[i].expenditure > budgets[i].budget) {

            printf("%s - Over by N$%.2f\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].budget);

            found = 1;
        }
    }

    if (!found)
        printf("No departments are over budget.\n");
}
