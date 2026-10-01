#include <stdio.h>
#include <string.h>

#define MAX_ASSETS 100

typedef struct {
    int assetID;
    char name[50];
    char type[30];       
    float purchaseValue;
    char department[50];
    char condition[30];    
} Asset;

void addAsset(Asset assets[], int *count);
void displayAssets(const Asset assets[], int count);
void searchAsset(const Asset assets[], int count);

void addAsset(Asset assets[], int *count) {
    if (*count >= MAX_ASSETS) {
        printf("\n[ERROR] Asset register is full. Cannot add more assets.\n");
        return;
    }

    Asset newAsset;
    
    printf("\n--- ADD NEW ASSET ---\n"
    printf("Enter Asset ID (integer): ");
    while (scanf("%d", &newAsset.assetID) != 1 || newAsset.assetID <= 0) {
        printf("[ERROR] Invalid ID. Please enter a positive integer: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Enter Asset Name: ");
    fgets(newAsset.name, sizeof(newAsset.name), stdin);
    newAsset.name[strcspn(newAsset.name, "\n")] = '\0';
    while (strlen(newAsset.name) == 0) {
        printf("[ERROR] Asset name cannot be empty. Enter Asset Name: ");
        fgets(newAsset.name, sizeof(newAsset.name), stdin);
        newAsset.name[strcspn(newAsset.name, "\n")] = '\0';
    }

    printf("Enter Asset Type (e.g., Vehicle, Computer, Building): ");
    fgets(newAsset.type, sizeof(newAsset.type), stdin);
    newAsset.type[strcspn(newAsset.type, "\n")] = '\0';

    printf("Enter Purchase Value (N$): ");
    while (scanf("%f", &newAsset.purchaseValue) != 1 || newAsset.purchaseValue < 0) {
        printf("[ERROR] Invalid value. Purchase value cannot be negative: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("Enter Department: ");
    fgets(newAsset.department, sizeof(newAsset.department), stdin);
    newAsset.department[strcspn(newAsset.department, "\n")] = '\0';

    printf("Enter Condition (e.g., Good, Fair, Poor): ");
    fgets(newAsset.condition, sizeof(newAsset.condition), stdin);
    newAsset.condition[strcspn(newAsset.condition, "\n")] = '\0';

    assets[*count] = newAsset;
    (*count)++;

    printf("\n[SUCCESS] Asset added successfully!\n");
}

void displayAssets(const Asset assets[], int count) {
    if (count == 0) {
        printf("\n[INFO] No assets currently registered in the system.\n");
        return;
    }

    printf("\n=================================================================================\n");
    printf("%-10s | %-20s | %-15s | %-12s | %-15s | %-10s\n", 
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d | %-20s | %-15s | N$%-10.2f | %-15s | %-10s\n",
               assets[i].assetID,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
    printf("=================================================================================\n");
}

void searchAsset(const Asset assets[], int count) {
    if (count == 0) {
        printf("\n[INFO] No assets available to search.\n");
        return;
    }

    int choice;
    printf("\n--- SEARCH ASSET ---\n");
    printf("1. Search by Asset ID\n");
    printf("2. Search by Asset Name\n");
    printf("Enter your choice: ");
    
    while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("[ERROR] Invalid choice. Enter 1 or 2: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    if (choice == 1) {
        int searchID;
        printf("Enter Asset ID to search: ");
        scanf("%d", &searchID);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (assets[i].assetID == searchID) {
                printf("\n[FOUND] Asset Details:\n");
                printf("ID         : %d\n", assets[i].assetID);
                printf("Name       : %s\n", assets[i].name);
                printf("Type       : %s\n", assets[i].type);
                printf("Value      : N$%.2f\n", assets[i].purchaseValue);
                printf("Department : %s\n", assets[i].department);
                printf("Condition  : %s\n", assets[i].condition);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\n[NOT FOUND] No asset with ID %d was found.\n", searchID);
        }

    } else {
        char searchName[50];
        printf("Enter Asset Name to search: ");
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strcspn(searchName, "\n")] = '\0';

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(assets[i].name, searchName) == 0) {
                printf("\n[FOUND] Asset Details:\n");
                printf("ID         : %d\n", assets[i].assetID);
                printf("Name       : %s\n", assets[i].name);
                printf("Type       : %s\n", assets[i].type);
                printf("Value      : N$%.2f\n", assets[i].purchaseValue);
                printf("Department : %s\n", assets[i].department);
                printf("Condition  : %s\n", assets[i].condition);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\n[NOT FOUND] No asset named '%s' was found.\n", searchName);
        }
    }
}