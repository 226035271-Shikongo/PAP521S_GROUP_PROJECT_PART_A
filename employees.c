#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

Employee employees[MAX_EMPLOYEES];
int empCount = 0;

double calculateSalary(Employee e)
{
    return e.basic + e.housing + e.transport;
}

int findEmployeeById(int id)
{
    for (int i = 0; i < empCount; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void printEmployeeHeader(void)
{
    printf("\n%-6s %-24s %-16s %-16s %14s\n", "ID", "Name", "Department", "Position", "Gross (N$)");
    printf("------------------------------------------------------------------------------\n");
}

static void printEmployeeRow(const Employee *e)
{
    printf("%-6d %-24.24s %-16.16s %-16.16s %14.2f\n",
           e->id, e->name, e->department, e->position, calculateSalary(*e));
}

static void printEmployeeDetails(const Employee *e)
{
    char label[EMP_NAME_LEN + EMP_DEPT_LEN + 8];

    strcpy(label, e->name);
    strcat(label, " - ");
    strcat(label, e->department);

    printf("\n%s\n", label);
    printf("  Employee ID : %d\n", e->id);
    printf("  Position    : %s\n", e->position);
    printf("  Gross Salary: N$%.2f\n", calculateSalary(*e));
}

void addEmployee(void)
{
    Employee e;

    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list is full (maximum %d).\n", MAX_EMPLOYEES);
        return;
    }

    printf("\n--- Add Employee ---\n");

    for (;;) {
        e.id = readInt("Enter Employee ID: ", 1, MAX_ID);
        if (findEmployeeById(e.id) == -1) {
            break;
        }
        printf("Employee ID %d already exists. Please use a different ID.\n", e.id);
    }

    readNonEmpty("Enter Name: ", e.name, sizeof e.name);
    readNonEmpty("Enter Department: ", e.department, sizeof e.department);
    readNonEmpty("Enter Position: ", e.position, sizeof e.position);

    for (;;) {
        e.basic = readMoney("Enter Basic Salary (N$): ");
        if (e.basic > 0) {
            break;
        }
        printf("Basic salary must be greater than zero.\n");
    }
    e.housing   = readMoney("Enter Housing Allowance (N$): ");
    e.transport = readMoney("Enter Transport Allowance (N$): ");

    employees[empCount++] = e;
    printf("Employee added successfully!\n");
}

void displayEmployees(void)
{
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printEmployeeHeader();
    for (int i = 0; i < empCount; i++) {
        printEmployeeRow(&employees[i]);
    }
}

void searchEmployee(void)
{
    int found = 0;

    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    printf("\nSearch by:\n1. Employee ID\n2. Name\n3. Department\n");
    int option = readMenuChoice("Enter your choice: ", 1, 3);

    if (option == 1) {
        int id = readInt("Enter Employee ID: ", 1, MAX_ID);
        int index = findEmployeeById(id);
        if (index != -1) {
            printEmployeeDetails(&employees[index]);
            found = 1;
        }
    } else {
        char keyword[EMP_NAME_LEN];
        readNonEmpty("Enter search text: ", keyword, sizeof keyword);

        for (int i = 0; i < empCount; i++) {
            const char *field = (option == 2) ? employees[i].name : employees[i].department;
            if (containsIgnoreCase(field, keyword)) {
                printEmployeeDetails(&employees[i]);
                found++;
            }
        }
    }

    if (!found) {
        printf("No matching employee found.\n");
    } else if (found > 1) {
        printf("\n%d employees found.\n", found);
    }
}

void displaySalaryInfo(void)
{
    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    int id = readInt("Enter Employee ID: ", 1, MAX_ID);
    int index = findEmployeeById(id);

    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    Employee e = employees[index];
    double gross = calculateSalary(e);

    printf("\nSalary information for %s (ID %d)\n", e.name, e.id);
    printf("  Basic salary       : N$%12.2f\n", e.basic);
    printf("  Housing allowance  : N$%12.2f\n", e.housing);
    printf("  Transport allowance: N$%12.2f\n", e.transport);
    printf("  --------------------------------------\n");
    printf("  Gross monthly      : N$%12.2f\n", gross);
    printf("  Gross annual       : N$%12.2f\n", gross * 12);
}

void employeeManagement(void)
{
    int choice;

    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n2. Display Employees\n3. Search Employee\n");
        printf("4. Salary Information\n5. Back\n");
        choice = readMenuChoice("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addEmployee();       break;
            case 2: displayEmployees();  break;
            case 3: searchEmployee();    break;
            case 4: displaySalaryInfo(); break;
            default: break;
        }
    } while (choice != 5);
}
