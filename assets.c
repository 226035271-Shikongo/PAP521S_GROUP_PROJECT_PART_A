#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

static const char *CONDITIONS[] = { "Excellent", "Good", "Fair", "Poor" };

int findAssetById(int id)
{
    for (int i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return i;
        }
    }
    return -1;
}

static void printAssetHeader(void)
{
    printf("\n%-6s %-22s %-14s %14s %-16s %-10s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printf("-----------------------------------------------------------------------------------\n");
}

static void printAssetRow(const Asset *a)
{
    printf("%-6d %-22.22s %-14.14s %14.2f %-16.16s %-10s\n",
           a->id, a->name, a->type, a->value, a->department, a->condition);
}

void addAsset(void)
{
    Asset a;

    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full (maximum %d).\n", MAX_ASSETS);
        return;
    }

    printf("\n--- Add Asset ---\n");

    for (;;) {
        a.id = readInt("Enter Asset ID: ", 1, MAX_ID);
        if (findAssetById(a.id) == -1) {
            break;
        }
        printf("Asset ID %d already exists. Please use a different ID.\n", a.id);
    }

    readNonEmpty("Enter Asset Name: ", a.name, sizeof a.name);
    readNonEmpty("Enter Asset Type (e.g. Vehicle, Computer, Building): ", a.type, sizeof a.type);

    for (;;) {
        a.value = readMoney("Enter Purchase Value (N$): ");
        if (a.value > 0) {
            break;
        }
        printf("Purchase value must be greater than zero.\n");
    }

    readNonEmpty("Enter Department: ", a.department, sizeof a.department);

    printf("Condition:\n1. Excellent\n2. Good\n3. Fair\n4. Poor\n");
    int c = readMenuChoice("Select condition: ", 1, 4);
    strcpy(a.condition, CONDITIONS[c - 1]);

    assets[assetCount++] = a;
    printf("Asset added successfully!\n");
}

void displayAssets(void)
{
    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printAssetHeader();
    for (int i = 0; i < assetCount; i++) {
        printAssetRow(&assets[i]);
    }
}

void searchAsset(void)
{
    int found = 0;

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("\nSearch by:\n1. Asset ID\n2. Name\n3. Type\n4. Department\n");
    int option = readMenuChoice("Enter your choice: ", 1, 4);

    if (option == 1) {
        int id = readInt("Enter Asset ID: ", 1, MAX_ID);
        int index = findAssetById(id);
        if (index != -1) {
            printAssetHeader();
            printAssetRow(&assets[index]);
            found = 1;
        }
    } else {
        char keyword[ASSET_NAME_LEN];
        readNonEmpty("Enter search text: ", keyword, sizeof keyword);

        for (int i = 0; i < assetCount; i++) {
            const char *field = assets[i].name;
            if (option == 3) {
                field = assets[i].type;
            } else if (option == 4) {
                field = assets[i].department;
            }
            if (containsIgnoreCase(field, keyword)) {
                if (found == 0) {
                    printAssetHeader();
                }
                printAssetRow(&assets[i]);
                found++;
            }
        }
    }

    if (!found) {
        printf("No matching asset found.\n");
    }
}

void assetManagement(void)
{
    int choice;

    do {
        printf("\n--- Asset Management ---\n");
        printf("1. Add Asset\n2. Display Assets\n3. Search Asset\n4. Back\n");
        choice = readMenuChoice("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            default: break;
        }
    } while (choice != 4);
}
