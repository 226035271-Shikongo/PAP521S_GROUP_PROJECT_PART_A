#include <stdio.h>
#include <string.h>

struct Employee {
    int ID;
    char name[25];
    char gender[10];
    char dateOfBirth[11];      
    char email[50];
    char cellPhoneNumber[11]; 
    char department[30];
    float salary;
    float housingAllowance;
    float transportAllowance;
};

struct Employee employee[100];
int employeeCount = 0;

void addEmployee();
void displayEmployee();
void searchEmployee();
void calculateSalary();

int main() {
    int choice;
    do {
        printf("\n==== EMPLOYEE MANAGEMENT ====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: searchEmployee(); break;
            case 4: calculateSalary(); break;
            case 5: printf("Exit\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

void addEmployee() {
    if (employeeCount >= 100) {
        printf("Employee list is full!\n");
        return;
    }
    printf("Enter Employee ID: ");
    scanf(" %d", &employee[employeeCount].ID);

    printf("Enter Name: ");
    scanf(" %24s", employee[employeeCount].name);

    printf("Enter Department: ");
    scanf(" %29s", employee[employeeCount].department);

    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf(" %10s", employee[employeeCount].dateOfBirth);

    printf("Enter Gender: ");
    scanf(" %9s", employee[employeeCount].gender);

    printf("Enter Email: ");
    scanf(" %49s", employee[employeeCount].email);

    printf("Enter Cellphone Number: ");
    scanf(" %10s", employee[employeeCount].cellPhoneNumber);

    printf("Enter Basic Salary: ");
    scanf(" %f", &employee[employeeCount].salary);

    printf("Enter Housing Allowance: ");
    scanf(" %f", &employee[employeeCount].housingAllowance);

    printf("Enter Transport Allowance: ");
    scanf(" %f", &employee[employeeCount].transportAllowance);

    employeeCount++;
    printf("\nEmployee added successfully!\n");
}

void displayEmployee() {
    int i;
    if (employeeCount == 0) {
        printf("\nNo employees found!\n");
        return;
    }
    for (i = 0; i < employeeCount; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", employee[i].ID);
        printf("Name: %s\n", employee[i].name);
        printf("Department: %s\n", employee[i].department);
        printf("Date of Birth: %s\n", employee[i].dateOfBirth);
        printf("Gender: %s\n", employee[i].gender);
        printf("Email: %s\n", employee[i].email);
        printf("Cellphone: %s\n", employee[i].cellPhoneNumber);
        printf("Salary: %.2f\n", employee[i].salary);
        printf("Housing Allowance: %.2f\n", employee[i].housingAllowance);
        printf("Transport Allowance: %.2f\n", employee[i].transportAllowance);
    }
}

void searchEmployee() {
    int ID, i, found = 0;

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &ID);

    for (i = 0; i < employeeCount; i++) {
        if (employee[i].ID == ID) {
            printf("\nEmployee found!\n");
            printf("Name: %s\n", employee[i].name);
            printf("Department: %s\n", employee[i].department);
            printf("Date of Birth: %s\n", employee[i].dateOfBirth);
            printf("Gender: %s\n", employee[i].gender);
            printf("Email: %s\n", employee[i].email);
            printf("Cellphone: %s\n", employee[i].cellPhoneNumber);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("\nEmployee not found!\n");
    }
}

void calculateSalary() {
    int ID, i, found = 0;
    float totalSalary;

    printf("\nEnter Employee ID: ");
    scanf("%d", &ID);

    for (i = 0; i < employeeCount; i++) {
        if (employee[i].ID == ID) {
            totalSalary = employee[i].salary + employee[i].housingAllowance
                        + employee[i].transportAllowance;

            printf("\nEmployee: %s\n", employee[i].name);
            printf("Basic Salary: %.2f\n", employee[i].salary);
            printf("Housing Allowance: %.2f\n", employee[i].housingAllowance);
            printf("Transport Allowance: %.2f\n", employee[i].transportAllowance);
            printf("Total Salary: %.2f\n", totalSalary);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("\nEmployee not found!\n");
    }
}
