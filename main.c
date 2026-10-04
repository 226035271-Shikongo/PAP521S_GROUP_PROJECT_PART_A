#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"
#include "utils.h"

void displayMenu(void)
{
    printf("\n========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int main(void)
{
    int choice;

    do {
        displayMenu();
        choice = readMenuChoice("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: employeeManagement(); break;
            case 2: budgetManagement();   break;
            case 3: supplierManagement(); break;
            case 4: assetManagement();    break;
            case 5: reports();            break;
            case 6: printf("Exiting system... Goodbye!\n"); break;
            default: break;
        }
    } while (choice != 6);

    return 0;
}
