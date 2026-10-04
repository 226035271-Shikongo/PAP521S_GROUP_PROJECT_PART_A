#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 50
#define SUP_NAME_LEN  50
#define SUP_EMAIL_LEN 50
#define SUP_PHONE_LEN 20
#define SUP_TOWN_LEN  30

typedef struct {
    int  id;
    char name[SUP_NAME_LEN];
    char email[SUP_EMAIL_LEN];
    char phone[SUP_PHONE_LEN];
    char town[SUP_TOWN_LEN];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supCount;

void supplierManagement(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
int  findSupplierById(int id);

#endif
