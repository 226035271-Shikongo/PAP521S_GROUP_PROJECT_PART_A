#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 30

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

void supplierManagement();
void addSupplier();
void displaySuppliers();
void searchSupplier();

#endif 
