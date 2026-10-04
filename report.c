#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* ---------- Employee Report ---------- */
void displayEmployeeReport(void) {
    if (employeeCount == 0) {
        printf("\nNo employees registered.\n");
        return;
    }

    double total = 0.0;
    double highest = employees[0].basicSalary;
    double lowest  = employees[0].basicSalary;

    for (int i = 0; i < employeeCount; i++) {
        double salary = employees[i].basicSalary;
        total += salary;

        if (salary > highest) highest = salary;
        if (salary < lowest)  lowest  = salary;
    }

    double average = total / employeeCount;

    printf("\n========== EMPLOYEE REPORT ==========\n");
    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", average);
    printf("Highest Salary  : N$%.2f\n", highest);
    printf("Lowest Salary   : N$%.2f\n", lowest);
    printf("=====================================\n");
}

/* ---------- Budget Report ---------- */
void displayBudgetReport(void) {
    if (budgetCount == 0) {
        printf("\nNo budget records found.\n");
        return;
    }

    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;

    for (int i = 0; i < budgetCount; i++) {
        totalAllocated   += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;
    }

    double remaining = totalAllocated - totalExpenditure;

    printf("\n========== BUDGET REPORT ==========\n");
    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Remaining Budget       : N$%.2f\n", remaining);

    printf("\nDepartments Exceeding Budget:\n");
    int found = 0;
    for (int i = 0; i < budgetCount; i++) {
        if (budgets[i].expenditure > budgets[i].allocatedBudget) {
            printf("  - %s (Over by N$%.2f)\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].allocatedBudget);
            found = 1;
        }
    }
    if (!found) {
        printf("  None - all departments are within budget.\n");
    }
    printf("====================================\n");
}

/* ---------- Supplier Report ---------- */
void displaySupplierReport(void) {
    if (supplierCount == 0) {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n========== SUPPLIER REPORT ==========\n");
    printf("%-8s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < supplierCount; i++) {
        printf("%-8s %-20s %-25s %-15s %-15s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }
    printf("================================================================================\n");
}

/* ---------- Asset Report ---------- */
void displayAssetReport(void) {
    if (assetCount == 0) {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\n========== ASSET REPORT ==========\n");
    printf("%-8s %-20s %-12s %-12s %-15s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < assetCount; i++) {
        printf("%-8s %-20s %-12s N$%-10.2f %-15s %-10s\n",
               assets[i].id,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
    printf("===========================================================================================\n");
}

/* ---------- All Reports ---------- */
void displayAllReports(void) {
    displayEmployeeReport();
    displayBudgetReport();
    displaySupplierReport();
    displayAssetReport();
}