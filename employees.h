#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define EMP_NAME_LEN  50
#define EMP_DEPT_LEN  30
#define EMP_POS_LEN   30

typedef struct {
    int    id;
    char   name[EMP_NAME_LEN];
    char   department[EMP_DEPT_LEN];
    char   position[EMP_POS_LEN];
    double basic;
    double housing;
    double transport;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int empCount;

void   employeeManagement(void);
void   addEmployee(void);
void   displayEmployees(void);
void   searchEmployee(void);
void   displaySalaryInfo(void);
int    findEmployeeById(int id);
double calculateSalary(Employee e);   /* gross monthly salary */

#endif
