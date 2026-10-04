#include <stdio.h> //allow us to use the printf() and scanf() to display and receive information
#include <string.h> //allows us to work with strings such as employee names, departments and ect
#include "employee.h"

#define MAX_EMPLOYEES 100
#define MAX_AMOUNT 10000000.0

struct Employee {
    int ID;
    char name[25];
    char gender[10];
    char dateOfBirth[11];
    char email[50];
    char cellPhoneNumber[11];
    char department[30];
    float salary;
    float housingAllowance;
    float transportAllowance;
};
//array to store employees
struct Employee employee[MAX_EMPLOYEES];
int employeeCount = 0;
//function declarations
void addEmployee();
void displayEmployee();
void searchEmployee();
void calculateSalary();

//validation function declarations
int getLine(const char *prompt, char *line, int size);
int getInt(const char *prompt, int *value, int min, int max);
int getFloat(const char *prompt, float *value, float min, float max);
int getText(const char *prompt, char *destination, int maxLength);
int isLetter(char c);
int isDigit(char c);
char lowerCase(char c);
int sameText(const char *a, const char *b);
int isLeapYear(int year);
int daysInMonth(int month, int year);
int isValidName(const char *text);
int isValidDate(const char *date);
int isValidEmail(const char *email);
int isValidCellphone(const char *number);
int idExists(int ID);

int main() {
    int choice = 0;
    do {
        printf("\n==== EMPLOYEE MANAGEMENT ====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Exit\n");
        if (!getInt("Enter your choice: ", &choice, 1, 5)) {
            printf("Invalid choice!\n");
            if (feof(stdin)) { //input has ended, so leave the program
                choice = 5;
            }
            continue;
        }

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: searchEmployee(); break;
            case 4: calculateSalary(); break;
            case 5: printf("Exit\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

int getLine(const char *prompt, char *line, int size) {
    int length, c;
    printf("%s", prompt);
    if (fgets(line, size, stdin) == NULL) {
        line[0] = '\0';
        return 0;
    }
    length = (int)strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
        length--;
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    if (length > 0 && line[length - 1] == '\r') {
        line[length - 1] = '\0';
    }
    return 1;
}

int getInt(const char *prompt, int *value, int min, int max) {
    char line[100];
    char extra;
    int number;
    if (!getLine(prompt, line, sizeof(line))) {
        return 0;
    }
    if (sscanf(line, "%d %c", &number, &extra) != 1) {
        return 0;
    }
    if (number < min || number > max) {
        return 0;
    }
    *value = number;
    return 1;
}

int getFloat(const char *prompt, float *value, float min, float max) {
    char line[100];
    char extra;
    float number;
    if (!getLine(prompt, line, sizeof(line))) {
        return 0;
    }
    if (sscanf(line, "%f %c", &number, &extra) != 1) {
        return 0;
    }
    if (!(number >= min && number <= max)) {
        return 0;
    }
    *value = number;
    return 1;
}

//Reads text that can not be empty or longer than maxLength
int getText(const char *prompt, char *destination, int maxLength) {
    char line[200];
    if (!getLine(prompt, line, sizeof(line))) {
        return 0;
    }
    if (strlen(line) == 0 || (int)strlen(line) > maxLength) {
        return 0;
    }
    strcpy(destination, line);
    return 1;
}

int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

char lowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (char)(c + 32);
    }
    return c;
}

//compares two words and ignores capital letters
int sameText(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (lowerCase(a[i]) != lowerCase(b[i])) {
            return 0;
        }
        i++;
    }
    return a[i] == b[i];
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

//name and department may only have letters and spaces
int isValidName(const char *text) {
    int i, letters = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (isLetter(text[i])) {
            letters++;
        } else if (text[i] != ' ') {
            return 0;
        }
    }
    return letters > 0 && text[0] != ' ';
}

//checks the format DD/MM/YYYY and that the date really exists
int isValidDate(const char *date) {
    int i, day, month, year;
    if (strlen(date) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (date[i] != '/') {
                return 0;
            }
        } else if (!isDigit(date[i])) {
            return 0;
        }
    }
    day = (date[0] - '0') * 10 + (date[1] - '0');
    month = (date[3] - '0') * 10 + (date[4] - '0');
    year = (date[6] - '0') * 1000 + (date[7] - '0') * 100
         + (date[8] - '0') * 10 + (date[9] - '0');

    if (year < 1900 || year > 2026) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > daysInMonth(month, year)) {
        return 0;
    }
    return 1;
}

//checks that the email has one @, something before it and a dot after it
int isValidEmail(const char *email) {
    int i, at = -1, lastDot = -1, length = (int)strlen(email);
    for (i = 0; i < length; i++) {
        if (email[i] == ' ') {
            return 0;
        }
        if (email[i] == '@') {
            if (at != -1) {
                return 0; //more than one @
            }
            at = i;
        }
        if (email[i] == '.' && at != -1) {
            lastDot = i;
        }
    }
    if (at < 1) {
        return 0;
    }
    if (lastDot == -1 || lastDot == at + 1 || lastDot >= length - 1) {
        return 0;
    }
    return 1;
}

//cellphone number must be exactly 10 digits
int isValidCellphone(const char *number) {
    int i;
    if (strlen(number) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (!isDigit(number[i])) {
            return 0;
        }
    }
    return 1;
}

//checks if an employee ID is already used
int idExists(int ID) {
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (employee[i].ID == ID) {
            return 1;
        }
    }
    return 0;
}

//Function to add employees
void addEmployee() {
    struct Employee newEmployee;
    char line[100];
    int valid;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }

    do {
        valid = getInt("Enter Employee ID: ", &newEmployee.ID, 1, 99);
        if (!valid) {
            printf("Invalid ID! Enter a whole number greater than 0.\n");
            if (feof(stdin)) return;
        } else if (idExists(newEmployee.ID)) {
            printf("Employee ID already exists!\n");
            valid = 0;
        }
    } while (!valid);

    do {
        valid = getText("Enter Name: ", newEmployee.name, 24) && isValidName(newEmployee.name);
        if (!valid) {
            printf("Invalid Name! Use letters only (maximum 24 characters).\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getText("Enter Department: ", newEmployee.department, 29) && isValidName(newEmployee.department);
        if (!valid) {
            printf("Invalid Department! Use letters only (maximum 29 characters).\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getText("Enter Date of Birth (DD/MM/YYYY): ", newEmployee.dateOfBirth, 10) && isValidDate(newEmployee.dateOfBirth);
        if (!valid) {
            printf("Invalid Date of Birth! Use DD/MM/YYYY with a real date.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getLine("Enter Gender: ", line, sizeof(line));
        if (valid && sameText(line, "Male")) {
            strcpy(newEmployee.gender, "Male");
        } else if (valid && sameText(line, "Female")) {
            strcpy(newEmployee.gender, "Female");
        } else {
            valid = 0;
            printf("Invalid Gender! Enter Male or Female.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getText("Enter Email: ", newEmployee.email, 49) && isValidEmail(newEmployee.email);
        if (!valid) {
            printf("Invalid Email! Example: name@email.com (maximum 49 characters).\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getText("Enter Cellphone Number: ", newEmployee.cellPhoneNumber, 10) && isValidCellphone(newEmployee.cellPhoneNumber);
        if (!valid) {
            printf("Invalid Cellphone Number! Enter exactly 10 digits.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getFloat("Enter Basic Salary: ", &newEmployee.salary, 0.01f, MAX_AMOUNT);
        if (!valid) {
            printf("Invalid Basic Salary! Enter a number greater than 0.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getFloat("Enter Housing Allowance: ", &newEmployee.housingAllowance, 0.0f, MAX_AMOUNT);
        if (!valid) {
            printf("Invalid Housing Allowance! Enter 0 or more.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    do {
        valid = getFloat("Enter Transport Allowance: ", &newEmployee.transportAllowance, 0.0f, MAX_AMOUNT);
        if (!valid) {
            printf("Invalid Transport Allowance! Enter 0 or more.\n");
            if (feof(stdin)) return;
        }
    } while (!valid);

    employee[employeeCount] = newEmployee;
    employeeCount++;
    printf("\nEmployee added successfully!\n");
}
//function to display employees
void displayEmployee() {
    int i;
    if (employeeCount == 0) {
        printf("\nNo employees found!\n");
        return;
    }
    for (i = 0; i < employeeCount; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", employee[i].ID);
        printf("Name: %s\n", employee[i].name);
        printf("Department: %s\n", employee[i].department);
        printf("Date of Birth: %s\n", employee[i].dateOfBirth);
        printf("Gender: %s\n", employee[i].gender);
        printf("Email: %s\n", employee[i].email);
        printf("Cellphone: %s\n", employee[i].cellPhoneNumber);
        printf("Salary: %.f\n", employee[i].salary);
        printf("Housing Allowance: %.f\n", employee[i].housingAllowance);
        printf("Transport Allowance: %.f\n", employee[i].transportAllowance);
    }
}
//function to search for an employee
void searchEmployee() {
    int ID, i, found = 0;

    if (employeeCount == 0) {
        printf("\nNo employees found!\n");
        return;
    }

    if (!getInt("\nEnter Employee ID to search: ", &ID, 1, 99)) {
        printf("Invalid ID! Enter a whole number greater than 0.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        if (employee[i].ID == ID) {
            printf("\nEmployee found!\n");
            printf("Name: %s\n", employee[i].name);
            printf("Department: %s\n", employee[i].department);
            printf("Date of Birth: %s\n", employee[i].dateOfBirth);
            printf("Gender: %s\n", employee[i].gender);
            printf("Email: %s\n", employee[i].email);
            printf("Cellphone: %s\n", employee[i].cellPhoneNumber);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("\nEmployee not found!\n");
    }
}
//function to calculate employee salary
void calculateSalary() {
    int ID, i, found = 0;
    float totalSalary;

    if (employeeCount == 0) {
        printf("\nNo employees found!\n");
        return;
    }

    if (!getInt("\nEnter Employee ID: ", &ID, 1, 99)) {
        printf("Invalid ID! Enter a whole number greater than 0.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        if (employee[i].ID == ID) {
            totalSalary = employee[i].salary + employee[i].housingAllowance
                        + employee[i].transportAllowance;

            printf("\nEmployee: %s\n", employee[i].name);
            printf("Basic Salary: %.f\n", employee[i].salary);
            printf("Housing Allowance: %.f\n", employee[i].housingAllowance);
            printf("Transport Allowance: %.f\n", employee[i].transportAllowance);
            printf("Total Salary: %.f\n", totalSalary);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("\nEmployee not found!\n");
    }
}
