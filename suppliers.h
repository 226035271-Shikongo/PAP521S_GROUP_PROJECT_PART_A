/*
 * suppliers.h
 * Supplier Management module - Municipal Financial Management System (MFMS)
 *
 * Responsibility: Student 3 - Supplier Management
 *
 * main.c calls supplierMenu() from the main menu.
 * report.c uses the shared suppliers[] array and supplierCount for the
 * Supplier Report.
 */

#ifndef SUPPLIERS_H
#define SUPPLIERS_H

/* Capacity and field sizes (sizes include the '\0' terminator) */
#define MAX_SUPPLIERS      50
#define SUP_ID_LEN         10
#define SUP_NAME_LEN       50
#define SUP_EMAIL_LEN      50
#define SUP_PHONE_LEN      16
#define SUP_TOWN_LEN       30

typedef struct
{
    char id[SUP_ID_LEN];
    char name[SUP_NAME_LEN];
    char email[SUP_EMAIL_LEN];
    char phone[SUP_PHONE_LEN];
    char town[SUP_TOWN_LEN];
} Supplier;

/* Shared supplier storage (defined in suppliers.c) */
extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

/* Menu entry point for the Supplier Management module */
void supplierMenu(void);

/* Core supplier operations */
void addSupplier(void);
void displaySuppliers(void);
void searchSupplierMenu(void);
void searchSupplierById(void);
void searchSupplierByName(void);
void searchSuppliersByTown(void);
void compareSuppliers(void);

/* Helpers that other modules may use */
int  getSupplierCount(void);
void displaySuppliersPerTown(void);
void loadSampleSuppliers(void);

#endif
