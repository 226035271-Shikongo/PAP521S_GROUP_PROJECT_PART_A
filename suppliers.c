/*
 * suppliers.c
 * Supplier Management module - Municipal Financial Management System (MFMS)
 *
 * Responsibility: Student 3 - Supplier Management
 *
 * Features:
 *   - Add a supplier (with input validation)
 *   - Display all suppliers
 *   - Search suppliers by ID, by name (partial match) or by town
 *   - Compare two suppliers side by side
 *
 * Suppliers are stored in an array of Supplier structures. supplierCount
 * holds how many suppliers are stored. Both are shared (via suppliers.h)
 * so report.c can produce the Supplier Report.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

/* ---------------------------------------------------------------------
 * Supplier storage (declared extern in suppliers.h)
 * --------------------------------------------------------------------- */
Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

/* Helper functions below are "static" so their names stay private to this
 * file and cannot clash with functions in other group members' modules. */

/* ---------------------------------------------------------------------
 * Private helper functions (only used inside this file)
 * --------------------------------------------------------------------- */

/* Reads one line of input into buffer and removes the newline.
 * Extra characters that do not fit are discarded.
 * Returns the length of the text read, or -1 if input has ended (EOF). */
static int readLine(char buffer[], int size)
{
    int length;
    int ch;

    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return -1;
    }

    length = (int)strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        length--;
    }
    else
    {
        /* Line was longer than the buffer: throw away the rest of it */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
    return length;
}

/* Removes spaces at the start and end of a string. Returns the new length. */
static int trimSpaces(char text[])
{
    int start = 0;
    int end = (int)strlen(text) - 1;
    int i;

    while (text[start] != '\0' && isspace((unsigned char)text[start]))
    {
        start++;
    }
    while (end >= start && isspace((unsigned char)text[end]))
    {
        end--;
    }

    for (i = 0; start + i <= end; i++)
    {
        text[i] = text[start + i];
    }
    text[i] = '\0';
    return i;
}

/* Reads a line, trims it and returns its length (-1 on EOF). */
static int readTrimmedLine(const char prompt[], char buffer[], int size)
{
    printf("%s", prompt);
    if (readLine(buffer, size) < 0)
    {
        return -1;
    }
    return trimSpaces(buffer);
}

/* Copies src into dest converting every letter to lowercase. */
static void toLowerCopy(const char src[], char dest[], int size)
{
    int i;
    for (i = 0; src[i] != '\0' && i < size - 1; i++)
    {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

/* Converts every letter in text to uppercase (used for supplier IDs). */
static void toUpperInPlace(char text[])
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        text[i] = (char)toupper((unsigned char)text[i]);
    }
}

/* Returns 1 if pattern appears anywhere in text, ignoring case. */
static int containsIgnoreCase(const char text[], const char pattern[])
{
    char lowerText[SUP_NAME_LEN];
    char lowerPattern[SUP_NAME_LEN];

    toLowerCopy(text, lowerText, SUP_NAME_LEN);
    toLowerCopy(pattern, lowerPattern, SUP_NAME_LEN);
    return strstr(lowerText, lowerPattern) != NULL;
}

/* Returns 1 if the two strings are equal, ignoring case. */
static int equalsIgnoreCase(const char first[], const char second[])
{
    char lowerFirst[SUP_EMAIL_LEN];
    char lowerSecond[SUP_EMAIL_LEN];

    toLowerCopy(first, lowerFirst, SUP_EMAIL_LEN);
    toLowerCopy(second, lowerSecond, SUP_EMAIL_LEN);
    return strcmp(lowerFirst, lowerSecond) == 0;
}

/* Reads a whole-number menu choice between min and max.
 * Returns the choice, 0 if the input is invalid, or -1 on EOF. */
static int readMenuChoice(int min, int max)
{
    char input[20];
    int length;
    int value = 0;
    int i;

    length = readTrimmedLine("Enter your choice: ", input, (int)sizeof(input));
    if (length < 0)
    {
        return -1;
    }
    if (length == 0)
    {
        return 0;
    }

    for (i = 0; i < length; i++)
    {
        if (!isdigit((unsigned char)input[i]))
        {
            return 0;
        }
        value = value * 10 + (input[i] - '0');
        if (value > max)
        {
            return 0;
        }
    }

    if (value < min)
    {
        return 0;
    }
    return value;
}

/* Waits for the user to press Enter before returning to a menu. */
static void pauseScreen(void)
{
    char dummy[5];
    printf("\nPress Enter to continue...");
    readLine(dummy, (int)sizeof(dummy));
}

/* ---------------------------------------------------------------------
 * Validation functions
 * --------------------------------------------------------------------- */

/* Supplier ID: 3 to 9 characters, letters and digits only (e.g. SUP001). */
static int isValidSupplierId(const char id[])
{
    int length = (int)strlen(id);
    int i;

    if (length < 3 || length > SUP_ID_LEN - 1)
    {
        return 0;
    }
    for (i = 0; i < length; i++)
    {
        if (!isalnum((unsigned char)id[i]))
        {
            return 0;
        }
    }
    return 1;
}

/* Supplier name: must not be empty and must contain at least one letter. */
static int isValidSupplierName(const char name[])
{
    int i;
    for (i = 0; name[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)name[i]))
        {
            return 1;
        }
    }
    return 0;
}

/* Email: no spaces, exactly one '@' that is not the first character,
 * and a '.' after the '@' with text on both sides of it. */
static int isValidEmail(const char email[])
{
    int length = (int)strlen(email);
    int atPosition = -1;
    int atCount = 0;
    int dotAfterAt = 0;
    int i;

    if (length < 5)
    {
        return 0;
    }

    for (i = 0; i < length; i++)
    {
        if (isspace((unsigned char)email[i]))
        {
            return 0;
        }
        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }
    }

    if (atCount != 1 || atPosition == 0)
    {
        return 0;
    }

    /* Look for a '.' that has at least one character before it (after '@')
     * and at least one character after it */
    for (i = atPosition + 2; i < length - 1; i++)
    {
        if (email[i] == '.')
        {
            dotAfterAt = 1;
        }
    }
    return dotAfterAt;
}

/* Telephone: optional leading '+', then 7 to 15 digits only. */
static int isValidPhone(const char phone[])
{
    int i = 0;
    int digits = 0;

    if (phone[0] == '+')
    {
        i = 1;
    }
    for (; phone[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
        digits++;
    }
    return digits >= 7 && digits <= 15;
}

/* Town: letters, spaces, hyphens and apostrophes only, at least one letter. */
static int isValidTown(const char town[])
{
    int hasLetter = 0;
    int i;

    for (i = 0; town[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)town[i]))
        {
            hasLetter = 1;
        }
        else if (town[i] != ' ' && town[i] != '-' && town[i] != '\'')
        {
            return 0;
        }
    }
    return hasLetter;
}

/* ---------------------------------------------------------------------
 * Lookup and display helpers
 * --------------------------------------------------------------------- */

/* Returns the array index of the supplier with this ID, or -1 if not found. */
static int findSupplierIndexById(const char id[])
{
    char upperId[SUP_ID_LEN];
    int i;

    strncpy(upperId, id, SUP_ID_LEN - 1);
    upperId[SUP_ID_LEN - 1] = '\0';
    toUpperInPlace(upperId);

    for (i = 0; i < supplierCount; i++)
    {
        if (strcmp(suppliers[i].id, upperId) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* Returns the index of a supplier that already uses this email, or -1. */
static int findSupplierIndexByEmail(const char email[])
{
    int i;
    for (i = 0; i < supplierCount; i++)
    {
        if (equalsIgnoreCase(suppliers[i].email, email))
        {
            return i;
        }
    }
    return -1;
}

static void printLine(void)
{
    printf("----------------------------------------------------------------------------------------\n");
}

static void printSupplierTableHeader(void)
{
    printLine();
    printf("%-9s %-24s %-15s %-14s %-24s\n", "ID", "Name", "Town", "Telephone", "Email");
    printLine();
}

static void printSupplierRow(int index)
{
    printf("%-9s %-24.24s %-15.15s %-14s %-24s\n",
           suppliers[index].id, suppliers[index].name, suppliers[index].town,
           suppliers[index].phone, suppliers[index].email);
}

/* Prints full details for one supplier. strcpy/strcat build the contact line. */
static void printSupplierDetails(int index)
{
    char contact[SUP_EMAIL_LEN + SUP_PHONE_LEN + 5];

    strcpy(contact, suppliers[index].phone);
    strcat(contact, " | ");
    strcat(contact, suppliers[index].email);

    printf("  Supplier ID : %s\n", suppliers[index].id);
    printf("  Name        : %s\n", suppliers[index].name);
    printf("  Town        : %s\n", suppliers[index].town);
    printf("  Contact     : %s\n", contact);
}

/* Returns a pointer to the part of an email after '@' (the domain). */
static const char *getEmailDomain(const char email[])
{
    const char *at = strchr(email, '@');
    if (at == NULL)
    {
        return "";
    }
    return at + 1;
}

/* Stores a new supplier at the end of the suppliers array. Returns 1 on success. */
static int storeSupplier(const char id[], const char name[], const char email[],
                         const char phone[], const char town[])
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        return 0;
    }

    strcpy(suppliers[supplierCount].id, id);
    toUpperInPlace(suppliers[supplierCount].id);
    strcpy(suppliers[supplierCount].name, name);
    strcpy(suppliers[supplierCount].email, email);
    strcpy(suppliers[supplierCount].phone, phone);
    strcpy(suppliers[supplierCount].town, town);
    supplierCount++;
    return 1;
}

/* ---------------------------------------------------------------------
 * Public functions (declared in suppliers.h)
 * --------------------------------------------------------------------- */

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("Registered suppliers: %d / %d\n\n", supplierCount, MAX_SUPPLIERS);
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Suppliers\n");
        printf("4. Compare Two Suppliers\n");
        printf("5. Return to Main Menu\n\n");

        choice = readMenuChoice(1, 5);

        switch (choice)
        {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                pauseScreen();
                break;
            case 3:
                searchSupplierMenu();
                break;
            case 4:
                compareSuppliers();
                pauseScreen();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            case -1:
                /* Input ended - leave the menu */
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
                break;
        }
    } while (choice != 5 && choice != -1);
}

void addSupplier(void)
{
    char id[SUP_ID_LEN + 20];
    char name[SUP_NAME_LEN + 20];
    char email[SUP_EMAIL_LEN + 20];
    char phone[SUP_PHONE_LEN + 20];
    char town[SUP_TOWN_LEN + 20];
    int length;
    int existing;

    printf("\n--- Add Supplier ---\n");

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Supplier list is full (%d suppliers). Cannot add more.\n", MAX_SUPPLIERS);
        return;
    }

    printf("(Enter 0 as the Supplier ID to cancel)\n");

    /* Supplier ID: valid format and not already used */
    while (1)
    {
        length = readTrimmedLine("Supplier ID (e.g. SUP001): ", id, (int)sizeof(id));
        if (length < 0 || strcmp(id, "0") == 0)
        {
            printf("Add supplier cancelled.\n");
            return;
        }
        if (!isValidSupplierId(id))
        {
            printf("  Invalid ID. Use 3 to %d letters/digits with no spaces.\n", SUP_ID_LEN - 1);
        }
        else if (findSupplierIndexById(id) != -1)
        {
            printf("  A supplier with ID %s already exists.\n", id);
        }
        else
        {
            break;
        }
    }

    /* Supplier name: not empty and not too long */
    while (1)
    {
        length = readTrimmedLine("Supplier name: ", name, (int)sizeof(name));
        if (length < 0)
        {
            return;
        }
        if (length == 0 || !isValidSupplierName(name))
        {
            printf("  Name cannot be empty and must contain letters.\n");
        }
        else if (length > SUP_NAME_LEN - 1)
        {
            printf("  Name is too long (maximum %d characters).\n", SUP_NAME_LEN - 1);
        }
        else
        {
            break;
        }
    }

    /* Email: valid format and not used by another supplier */
    while (1)
    {
        length = readTrimmedLine("Email: ", email, (int)sizeof(email));
        if (length < 0)
        {
            return;
        }
        if (length > SUP_EMAIL_LEN - 1)
        {
            printf("  Email is too long (maximum %d characters).\n", SUP_EMAIL_LEN - 1);
        }
        else if (!isValidEmail(email))
        {
            printf("  Invalid email. Example: sales@company.com.na\n");
        }
        else if ((existing = findSupplierIndexByEmail(email)) != -1)
        {
            printf("  This email is already used by supplier %s (%s).\n",
                   suppliers[existing].id, suppliers[existing].name);
        }
        else
        {
            break;
        }
    }

    /* Telephone: digits only with optional leading '+' */
    while (1)
    {
        length = readTrimmedLine("Telephone number (e.g. 0612345678): ", phone, (int)sizeof(phone));
        if (length < 0)
        {
            return;
        }
        if (length > SUP_PHONE_LEN - 1 || !isValidPhone(phone))
        {
            printf("  Invalid number. Use 7 to 15 digits, optionally starting with '+'.\n");
        }
        else
        {
            break;
        }
    }

    /* Town / location */
    while (1)
    {
        length = readTrimmedLine("Town/Location: ", town, (int)sizeof(town));
        if (length < 0)
        {
            return;
        }
        if (length == 0 || !isValidTown(town))
        {
            printf("  Invalid town. Use letters, spaces or hyphens only.\n");
        }
        else if (length > SUP_TOWN_LEN - 1)
        {
            printf("  Town name is too long (maximum %d characters).\n", SUP_TOWN_LEN - 1);
        }
        else
        {
            break;
        }
    }

    if (storeSupplier(id, name, email, phone, town))
    {
        printf("\nSupplier added successfully:\n");
        printSupplierDetails(supplierCount - 1);
    }
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- Registered Suppliers ---\n");
    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printSupplierTableHeader();
    for (i = 0; i < supplierCount; i++)
    {
        printSupplierRow(i);
    }
    printLine();
    printf("Total suppliers: %d\n", supplierCount);
}

void searchSupplierMenu(void)
{
    int choice;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered yet. Add a supplier first.\n");
        return;
    }

    do
    {
        printf("\n--- Search Suppliers ---\n");
        printf("1. Search by Supplier ID\n");
        printf("2. Search by Name (partial match)\n");
        printf("3. Search by Town/Location\n");
        printf("4. Back to Supplier Menu\n\n");

        choice = readMenuChoice(1, 4);

        switch (choice)
        {
            case 1:
                searchSupplierById();
                pauseScreen();
                break;
            case 2:
                searchSupplierByName();
                pauseScreen();
                break;
            case 3:
                searchSuppliersByTown();
                pauseScreen();
                break;
            case 4:
            case -1:
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
                break;
        }
    } while (choice != 4 && choice != -1);
}

void searchSupplierById(void)
{
    char id[SUP_ID_LEN + 20];
    int index;

    if (readTrimmedLine("Enter Supplier ID: ", id, (int)sizeof(id)) <= 0)
    {
        printf("No ID entered.\n");
        return;
    }

    index = findSupplierIndexById(id);
    if (index == -1)
    {
        printf("No supplier found with ID \"%s\".\n", id);
    }
    else
    {
        printf("\nSupplier found:\n");
        printSupplierDetails(index);
    }
}

void searchSupplierByName(void)
{
    char keyword[SUP_NAME_LEN];
    int found = 0;
    int i;

    if (readTrimmedLine("Enter name or part of name: ", keyword, (int)sizeof(keyword)) <= 0)
    {
        printf("No search text entered.\n");
        return;
    }

    for (i = 0; i < supplierCount; i++)
    {
        if (containsIgnoreCase(suppliers[i].name, keyword))
        {
            if (found == 0)
            {
                printf("\nSuppliers matching \"%s\":\n", keyword);
                printSupplierTableHeader();
            }
            printSupplierRow(i);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No supplier names contain \"%s\".\n", keyword);
    }
    else
    {
        printLine();
        printf("%d supplier(s) found.\n", found);
    }
}

void searchSuppliersByTown(void)
{
    char town[SUP_TOWN_LEN];
    int found = 0;
    int i;

    if (readTrimmedLine("Enter town/location: ", town, (int)sizeof(town)) <= 0)
    {
        printf("No town entered.\n");
        return;
    }

    for (i = 0; i < supplierCount; i++)
    {
        if (equalsIgnoreCase(suppliers[i].town, town))
        {
            if (found == 0)
            {
                printf("\nSuppliers located in %s:\n", town);
                printSupplierTableHeader();
            }
            printSupplierRow(i);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No suppliers are located in \"%s\".\n", town);
    }
    else
    {
        printLine();
        printf("%d of %d supplier(s) are located in %s.\n", found, supplierCount, town);
    }
}

void compareSuppliers(void)
{
    char firstId[SUP_ID_LEN + 20];
    char secondId[SUP_ID_LEN + 20];
    int first;
    int second;
    int nameOrder;

    printf("\n--- Compare Two Suppliers ---\n");
    if (supplierCount < 2)
    {
        printf("At least two suppliers are needed to compare.\n");
        return;
    }

    readTrimmedLine("Enter first Supplier ID : ", firstId, (int)sizeof(firstId));
    first = findSupplierIndexById(firstId);
    if (first == -1)
    {
        printf("No supplier found with ID \"%s\".\n", firstId);
        return;
    }

    readTrimmedLine("Enter second Supplier ID: ", secondId, (int)sizeof(secondId));
    second = findSupplierIndexById(secondId);
    if (second == -1)
    {
        printf("No supplier found with ID \"%s\".\n", secondId);
        return;
    }
    if (first == second)
    {
        printf("Both IDs refer to the same supplier. Enter two different suppliers.\n");
        return;
    }

    /* Side-by-side comparison */
    printf("\n%-12s | %-30s | %-30s\n", "Field", suppliers[first].id, suppliers[second].id);
    printf("-------------+--------------------------------+-------------------------------\n");
    printf("%-12s | %-30.30s | %-30.30s\n", "Name", suppliers[first].name, suppliers[second].name);
    printf("%-12s | %-30.30s | %-30.30s\n", "Town", suppliers[first].town, suppliers[second].town);
    printf("%-12s | %-30.30s | %-30.30s\n", "Telephone", suppliers[first].phone, suppliers[second].phone);
    printf("%-12s | %-30.30s | %-30.30s\n", "Email", suppliers[first].email, suppliers[second].email);

    /* Comparison results */
    printf("\nComparison results:\n");

    if (equalsIgnoreCase(suppliers[first].town, suppliers[second].town))
    {
        printf("  - Both suppliers are located in %s.\n", suppliers[first].town);
    }
    else
    {
        printf("  - Different locations: %s vs %s.\n", suppliers[first].town, suppliers[second].town);
    }

    if (equalsIgnoreCase(getEmailDomain(suppliers[first].email), getEmailDomain(suppliers[second].email)))
    {
        printf("  - Same email domain (%s): they may belong to the same company.\n",
               getEmailDomain(suppliers[first].email));
    }
    else
    {
        printf("  - Different email domains.\n");
    }

    if (strcmp(suppliers[first].phone, suppliers[second].phone) == 0)
    {
        printf("  - WARNING: both suppliers use the same telephone number.\n");
    }

    nameOrder = strcmp(suppliers[first].name, suppliers[second].name);
    if (nameOrder < 0)
    {
        printf("  - Alphabetically, \"%s\" comes before \"%s\".\n", suppliers[first].name, suppliers[second].name);
    }
    else if (nameOrder > 0)
    {
        printf("  - Alphabetically, \"%s\" comes before \"%s\".\n", suppliers[second].name, suppliers[first].name);
    }
    else
    {
        printf("  - Both suppliers have the same name.\n");
    }
}

int getSupplierCount(void)
{
    return supplierCount;
}

/* Shows how many suppliers are registered in each town.
 * report.c may call this after displaySupplierReport() for extra detail. */
void displaySuppliersPerTown(void)
{
    char countedTowns[MAX_SUPPLIERS][SUP_TOWN_LEN];
    int townTotals[MAX_SUPPLIERS];
    int townCount = 0;
    int i;
    int j;
    int alreadyCounted;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered.\n");
        return;
    }

    /* Count how many suppliers are in each town */
    for (i = 0; i < supplierCount; i++)
    {
        alreadyCounted = 0;
        for (j = 0; j < townCount; j++)
        {
            if (equalsIgnoreCase(countedTowns[j], suppliers[i].town))
            {
                townTotals[j]++;
                alreadyCounted = 1;
                break;
            }
        }
        if (!alreadyCounted)
        {
            strcpy(countedTowns[townCount], suppliers[i].town);
            townTotals[townCount] = 1;
            townCount++;
        }
    }

    printf("\nSuppliers per town:\n");
    for (j = 0; j < townCount; j++)
    {
        printf("  %-20s : %d\n", countedTowns[j], townTotals[j]);
    }
}

/* Loads example suppliers so the module can be demonstrated quickly.
 * Only loads if the list is empty, so it is safe to call more than once. */
void loadSampleSuppliers(void)
{
    if (supplierCount > 0)
    {
        return;
    }
    storeSupplier("SUP001", "Namib Office Supplies", "sales@namiboffice.com.na", "0612345678", "Windhoek");
    storeSupplier("SUP002", "Kalahari Construction", "info@kalaharibuild.com.na", "0642223344", "Walvis Bay");
    storeSupplier("SUP003", "Etosha IT Solutions", "support@etoshait.com.na", "0613456789", "Windhoek");
    storeSupplier("SUP004", "Swakop Fleet Services", "fleet@swakopfleet.com.na", "0644112233", "Swakopmund");
    storeSupplier("SUP005", "Oshana Cleaning Services", "admin@oshanaclean.com.na", "0652201100", "Oshakati");
}
