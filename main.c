#include <stdio.h>
#include "validation.h"

void displayMenu(void);
void employeeMenu(void);
void budgetMenu(void);
void supplierMenu(void);
void assetMenu(void);
void reportsMenu(void);

int main(void)
{
    int choice;

    do
    {
        displayMenu();

        choice = getMenuChoice(1, 6);

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                budgetMenu();
                break;

            case 3:
                supplierMenu();
                break;

            case 4:
                assetMenu();
                break;

            case 5:
                reportsMenu();
                break;

            case 6:
                printf("\nExiting Municipal Financial Management System...\n");
                printf("Thank you for using the system.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}

void displayMenu(void)
{
    printf("\n");
    printf("========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("========================================\n");
}


void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("--------- EMPLOYEE MANAGEMENT ---------\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Back to Main Menu\n");
        printf("---------------------------------------\n");

        choice = getMenuChoice(1, 5);

        switch (choice)
        {
            case 1:
                printf("\nEmployee module: Add Employee\n");
                break;

            case 2:
                printf("\nEmployee module: Display Employees\n");
                break;

            case 3:
                printf("\nEmployee module: Search Employee\n");
                break;

            case 4:
                printf("\nEmployee module: Calculate Salary\n");
                break;

            case 5:
                printf("\nReturning to main menu...\n");
                break;
        }

    } while (choice != 5);
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("----------- BUDGET MANAGEMENT ----------\n");
        printf("1. Enter Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budget Information\n");
        printf("4. Check Budget Status\n");
        printf("5. Back to Main Menu\n");
        printf("----------------------------------------\n");

        choice = getMenuChoice(1, 5);

        switch (choice)
        {
            case 1:
                printf("\nBudget module: Enter Department Budget\n");
                break;

            case 2:
                printf("\nBudget module: Enter Expenditure\n");
                break;

            case 3:
                printf("\nBudget module: Display Budget Information\n");
                break;

            case 4:
                printf("\nBudget module: Check Budget Status\n");
                break;

            case 5:
                printf("\nReturning to main menu...\n");
                break;
        }

    } while (choice != 5);
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("---------- SUPPLIER MANAGEMENT ---------\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("----------------------------------------\n");

        choice = getMenuChoice(1, 4);

        switch (choice)
        {
            case 1:
                printf("\nSupplier module: Add Supplier\n");
                break;

            case 2:
                printf("\nSupplier module: Display Suppliers\n");
                break;

            case 3:
                printf("\nSupplier module: Search Supplier\n");
                break;

            case 4:
                printf("\nReturning to main menu...\n");
                break;
        }

    } while (choice != 4);
}

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("------------ ASSET MANAGEMENT ----------\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        printf("----------------------------------------\n");

        choice = getMenuChoice(1, 4);

        switch (choice)
        {
            case 1:
                printf("\nAsset module: Add Asset\n");
                break;

            case 2:
                printf("\nAsset module: Display Assets\n");
                break;

            case 3:
                printf("\nAsset module: Search Asset\n");
                break;

            case 4:
                printf("\nReturning to main menu...\n");
                break;
        }

    } while (choice != 4);
}


/* Reports module */
void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("---------------- REPORTS ---------------\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        printf("----------------------------------------\n");

        choice = getMenuChoice(1, 5);

        switch (choice)
        {
            case 1:
                printf("\nReports module: Employee Report\n");
                break;

            case 2:
                printf("\nReports module: Budget Report\n");
                break;

            case 3:
                printf("\nReports module: Supplier Report\n");
                break;

            case 4:
                printf("\nReports module: Asset Report\n");
                break;

            case 5:
                printf("\nReturning to main menu...\n");
                break;
        }

    } while (choice != 5);
}