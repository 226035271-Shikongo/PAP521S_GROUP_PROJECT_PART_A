#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPTS     20
#define DEPT_NAME_LEN 30

typedef struct {
    char   deptName[DEPT_NAME_LEN];
    double allocated;
    double spent;
} Budget;

extern Budget budgets[MAX_DEPTS];
extern int deptCount;

void        budgetManagement(void);
void        addBudget(void);
void        recordExpenditure(void);
void        displayBudgets(void);
void        showExceededBudgets(void);
int         findBudgetByName(const char *name);
double      calculateBudget(double allocated, double spent);  /* remaining budget */
const char *budgetStatus(double remaining);

#endif
