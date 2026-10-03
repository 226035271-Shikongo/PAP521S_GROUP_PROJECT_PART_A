#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 10

typedef struct
{
    char department[30];
    float allocatedBudget;
    float expenditure;
} Budget;

/* Budget Management functions */
void addBudget(Budget budgets[], int *count);
void enterExpenditure(Budget budgets[], int count);
void displayBudgets(Budget budgets[], int count);
void showOverBudget(Budget budgets[], int count);
void budgetMenu(Budget budgets[], int *count);

#endif