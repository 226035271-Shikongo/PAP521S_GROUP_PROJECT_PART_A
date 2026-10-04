#include <stdio.h>
#include "assets.h"
#include "budget.h"
#include "employees.h"
#include "reports.h"
#include "suppliers.h"

void reports() {
    printf("\n--- Employee Report ---\n");
    displayEmployees();

    printf("\n--- Budget Report ---\n");
    displayBudgets();

    printf("\n--- Supplier Report ---\n");
    displaySuppliers();

    printf("\n--- Asset Report ---\n");
    displayAssets();
}
