#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_EMPLOYEES 100
#define MAX_AMOUNT 10000000.0

typedef struct
{
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
} Employee;

//Employee Management functions 
void addEmployee(void);
void displayEmployee(void);
void searchEmployee(void);
void calculateSalary(void);

// Input functions 
int getLine(const char *prompt, char *line, int size);
int getInt(const char *prompt, int *value, int min, int max);
int getFloat(const char *prompt, float *value, float min, float max);
int getText(const char *prompt, char *destination, int maxLength);

//Text functions 
int isLetter(char c);
int isDigit(char c);
char lowerCase(char c);
int sameText(const char *a, const char *b);

//Date functions 
int isLeapYear(int year);
int daysInMonth(int month, int year);

//Validation functions 
int isValidName(const char *text);
int isValidDate(const char *date);
int isValidEmail(const char *email);
int isValidCellphone(const char *number);
int idExists(int ID);

#endif
