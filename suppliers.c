#include <stdio.h>
#include <string.h>
#include "suppliers.h"

Supplier suppliers[MAX_SUPPLIERS];
int supCount = 0;

void addSupplier() {
    Supplier s;
    printf("Enter Supplier ID: "); scanf("%d", &s.id);
    printf("Enter Name: "); scanf("%s", s.name);
    printf("Enter Email: "); scanf("%s", s.email);
    printf("Enter Phone: "); scanf("%s", s.phone);
    printf("Enter Town: "); scanf("%s", s.town);
    suppliers[supCount++] = s;
}

void displaySuppliers() {
    for (int i = 0; i < supCount; i++) {
        printf("%d | %s | %s | %s | %s\n", suppliers[i].id, suppliers[i].name,
               suppliers[i].email, suppliers[i].phone, suppliers[i].town);
    }
}

void searchSupplier() {
    char name[50];
    printf("Enter Supplier Name to search: ");
    scanf("%s", name);
    for (int i = 0; i < supCount; i++) {
        if (strcmp(suppliers[i].name, name) == 0) {
            printf("Found: %s in %s\n", suppliers[i].name, suppliers[i].town);
            return;
        }
    }
    printf("Supplier not found.\n");
}

void supplierManagement() {
    int choice;
    do {
        printf("\n--- Supplier Management ---\n");
        printf("1. Add Supplier\n2. Display Suppliers\n3. Search Supplier\n4. Back\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
