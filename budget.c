#include <stdio.h>
#include "budget.h"

Budget budgets[MAX_DEPTS];
int deptCount = 0;

void addBudget() {
    Budget b;
    printf("Enter Department: "); scanf("%s", b.deptName);
    printf("Enter Allocated Budget: "); scanf("%f", &b.allocated);
    printf("Enter Expenditure: "); scanf("%f", &b.spent);
    budgets[deptCount++] = b;
}

void displayBudgets() {
    for (int i = 0; i < deptCount; i++) {
        float remaining = budgets[i].allocated - budgets[i].spent;
        printf("%s | Allocated: %.2f | Spent: %.2f | Remaining: %.2f | Status: %s\n",
               budgets[i].deptName, budgets[i].allocated, budgets[i].spent, remaining,
               (remaining >= 0) ? "WITHIN BUDGET" : "EXCEEDED");
    }
}

void budgetManagement() {
    int choice;
    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add Budget\n2. Display Budgets\n3. Back\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}
