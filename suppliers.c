#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

Supplier suppliers[MAX_SUPPLIERS];
int supCount = 0;

int findSupplierById(int id)
{
    for (int i = 0; i < supCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* Returns 1 if another supplier already uses this email address. */
static int emailExists(const char *email)
{
    for (int i = 0; i < supCount; i++) {
        if (equalsIgnoreCase(suppliers[i].email, email)) {
            return 1;
        }
    }
    return 0;
}

static void printSupplierHeader(void)
{
    printf("\n%-6s %-22s %-26s %-16s %-14s\n", "ID", "Name", "Email", "Phone", "Town");
    printf("---------------------------------------------------------------------------------\n");
}

static void printSupplierRow(const Supplier *s)
{
    printf("%-6d %-22.22s %-26.26s %-16.16s %-14.14s\n",
           s->id, s->name, s->email, s->phone, s->town);
}

void addSupplier(void)
{
    Supplier s;

    if (supCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full (maximum %d).\n", MAX_SUPPLIERS);
        return;
    }

    printf("\n--- Add Supplier ---\n");

    for (;;) {
        s.id = readInt("Enter Supplier ID: ", 1, MAX_ID);
        if (findSupplierById(s.id) == -1) {
            break;
        }
        printf("Supplier ID %d already exists. Please use a different ID.\n", s.id);
    }

    readNonEmpty("Enter Supplier Name: ", s.name, sizeof s.name);

    for (;;) {
        readEmail("Enter Email: ", s.email, sizeof s.email);
        if (!emailExists(s.email)) {
            break;
        }
        printf("A supplier with that email already exists.\n");
    }

    readPhone("Enter Telephone Number: ", s.phone, sizeof s.phone);
    readNonEmpty("Enter Town/Location: ", s.town, sizeof s.town);

    suppliers[supCount++] = s;
    printf("Supplier added successfully!\n");
}

void displaySuppliers(void)
{
    if (supCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printSupplierHeader();
    for (int i = 0; i < supCount; i++) {
        printSupplierRow(&suppliers[i]);
    }
}

void searchSupplier(void)
{
    int found = 0;

    if (supCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\nSearch by:\n1. Supplier ID\n2. Name\n3. Town/Location\n");
    int option = readMenuChoice("Enter your choice: ", 1, 3);

    if (option == 1) {
        int id = readInt("Enter Supplier ID: ", 1, MAX_ID);
        int index = findSupplierById(id);
        if (index != -1) {
            printSupplierHeader();
            printSupplierRow(&suppliers[index]);
            found = 1;
        }
    } else {
        char keyword[SUP_NAME_LEN];
        readNonEmpty("Enter search text: ", keyword, sizeof keyword);

        for (int i = 0; i < supCount; i++) {
            const char *field = (option == 2) ? suppliers[i].name : suppliers[i].town;
            if (containsIgnoreCase(field, keyword)) {
                if (found == 0) {
                    printSupplierHeader();
                }
                printSupplierRow(&suppliers[i]);
                found++;
            }
        }
    }

    if (!found) {
        printf("No matching supplier found.\n");
    }
}

void supplierManagement(void)
{
    int choice;

    do {
        printf("\n--- Supplier Management ---\n");
        printf("1. Add Supplier\n2. Display Suppliers\n3. Search Supplier\n4. Back\n");
        choice = readMenuChoice("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            default: break;
        }
    } while (choice != 4);
}
