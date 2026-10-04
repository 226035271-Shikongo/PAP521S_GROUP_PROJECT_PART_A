#include <stdio.h>
#include "assets.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

void addAsset() {
    Asset a;
    printf("Enter Asset ID: "); scanf("%d", &a.id);
    printf("Enter Name: "); scanf("%s", a.name);
    printf("Enter Type: "); scanf("%s", a.type);
    printf("Enter Value: "); scanf("%f", &a.value);
    printf("Enter Department: "); scanf("%s", a.department);
    printf("Enter Condition: "); scanf("%s", a.condition);
    assets[assetCount++] = a;
}

void displayAssets() {
    for (int i = 0; i < assetCount; i++) {
        printf("%d | %s | %s | %.2f | %s | %s\n", assets[i].id, assets[i].name,
               assets[i].type, assets[i].value, assets[i].department, assets[i].condition);
    }
}

void assetManagement() {
    int choice;
    do {
        printf("\n--- Asset Management ---\n");
        printf("1. Add Asset\n2. Display Assets\n3. Back\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}
