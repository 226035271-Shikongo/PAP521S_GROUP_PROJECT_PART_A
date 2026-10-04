#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

Employee employees[MAX_EMPLOYEES];
int empCount = 0;

void addEmployee() {
    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list full!\n");
        return;
    }
    Employee e;
    printf("Enter ID: "); scanf("%d", &e.id);
    while (getchar() != '\n');
    printf("Enter Name: "); fgets(e.name, sizeof(e.name), stdin);e.name[strcspn(e.name, "\n")] = 0;
    printf("Enter Department: "); fgets(e.department, sizeof(e.department), stdin); e.department[strcspn(e.department, "\n")] = 0; 
    printf("Enter Basic Salary: "); scanf("%f", &e.basic);
    printf("Enter Housing Allowance: "); scanf("%f", &e.housing);
    printf("Enter Transport Allowance: "); scanf("%f", &e.transport);
    employees[empCount++] = e;
    printf("Employee added successfully!\n");
}

void displayEmployees() {
    for (int i = 0; i < empCount; i++) {
        printf("%d | %s | %s | Salary: %.2f\n", employees[i].id,
               employees[i].name, employees[i].department,
               employees[i].basic + employees[i].housing + employees[i].transport);
    }
}

void searchEmployee() {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < empCount; i++) {
        if (employees[i].id == id) {
            printf("Found: %s in %s\n", employees[i].name, employees[i].department);
            return;
        }
    }
    printf("Employee not found.\n");
}

void employeeManagement() {
    int choice;
    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n2. Display Employees\n3. Search Employee\n4. Back\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
