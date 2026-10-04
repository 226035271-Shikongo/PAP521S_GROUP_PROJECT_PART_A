#include <stdio.h>
#include "assets.h"
#include "budget.h"
#include "employees.h"
#include "reports.h"
#include "suppliers.h"
#include "utils.h"

void employeeReport(void)
{
    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    double total = 0.0;
    double highest = calculateSalary(employees[0]);
    double lowest = highest;
    int highIndex = 0;
    int lowIndex = 0;

    for (int i = 0; i < empCount; i++) {
        double salary = calculateSalary(employees[i]);
        total += salary;
        if (salary > highest) {
            highest = salary;
            highIndex = i;
        }
        if (salary < lowest) {
            lowest = salary;
            lowIndex = i;
        }
    }

    printf("Total Employees: %d\n", empCount);
    printf("Average Salary : N$%.2f\n", total / empCount);
    printf("Highest Salary : N$%.2f (%s)\n", highest, employees[highIndex].name);
    printf("Lowest Salary  : N$%.2f (%s)\n", lowest, employees[lowIndex].name);
    displayEmployees();
}

void budgetReport(void)
{
    printf("\n========== BUDGET REPORT ==========\n");

    if (deptCount == 0) {
        printf("No department budgets registered yet.\n");
        return;
    }

    double totalAllocated = 0.0;
    double totalSpent = 0.0;

    for (int i = 0; i < deptCount; i++) {
        totalAllocated += budgets[i].allocated;
        totalSpent += budgets[i].spent;
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure     : N$%.2f\n", totalSpent);
    printf("Total Remaining Budget: N$%.2f\n", calculateBudget(totalAllocated, totalSpent));

    printf("\nDepartments exceeding budget:\n");
    showExceededBudgets();

    displayBudgets();
}

void supplierReport(void)
{
    printf("\n========== SUPPLIER REPORT ==========\n");
    printf("Total Suppliers: %d\n", supCount);
    displaySuppliers();
}

void assetReport(void)
{
    printf("\n========== ASSET REPORT ==========\n");

    double totalValue = 0.0;
    for (int i = 0; i < assetCount; i++) {
        totalValue += assets[i].value;
    }

    printf("Total Assets      : %d\n", assetCount);
    printf("Total Asset Value : N$%.2f\n", totalValue);
    displayAssets();
}

void reports(void)
{
    int choice;

    do {
        printf("\n--- Reports ---\n");
        printf("1. Employee Report\n2. Budget Report\n3. Supplier Report\n");
        printf("4. Asset Report\n5. All Reports\n6. Back\n");
        choice = readMenuChoice("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5:
                employeeReport();
                budgetReport();
                supplierReport();
                assetReport();
                break;
            default: break;
        }
    } while (choice != 6);
}
