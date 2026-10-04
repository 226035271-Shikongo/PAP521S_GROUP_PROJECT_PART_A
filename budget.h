#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPTS 20

typedef struct {
    char deptName[30];
    float allocated;
    float spent;
} Budget;

void budgetManagement();
void addBudget();
void displayBudgets();
float calculateBudget(float allocated, float spent);

#endif
