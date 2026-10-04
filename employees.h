#ifndef EMPLOYEES_H   // Start include guard
#define EMPLOYEES_H

#define MAX_EMPLOYEES 50

typedef struct {
    int id;
    char name[50];
    char department[30];
    float basic;
    float housing;
    float transport;
} Employee;

void employeeManagement();
void addEmployee();
void displayEmployees();
void searchEmployee();
float calculateSalary(Employee e);

#endif
