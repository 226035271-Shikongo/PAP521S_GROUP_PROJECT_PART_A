#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "utils.h"

#define MAX_MONEY 1000000000000.0

/* Removes spaces at the start and end of a string. */
static void trimInPlace(char *s)
{
    size_t len = strlen(s);
    size_t start = 0;

    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }
    while (len > start && isspace((unsigned char)s[len - 1])) {
        len--;
    }
    memmove(s, s + start, len - start);
    s[len - start] = '\0';
}

/* Reads one line with fgets (so spaces are allowed and the buffer cannot overflow).
   Lines that are too long are rejected. If input ends (EOF) the program exits
   cleanly instead of looping forever. */
void readLine(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(buf, (int)size, stdin) == NULL) {
            printf("\nInput closed. Exiting program.\n");
            exit(EXIT_SUCCESS);
        }

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        } else if (len == size - 1) {
            int c = getchar();                 /* buffer full: was that the end of the line? */
            if (c != '\n' && c != EOF) {
                while (c != '\n' && c != EOF) {
                    c = getchar();             /* throw away the rest of the long line */
                }
                printf("Input too long (maximum %zu characters). Please try again.\n", size - 1);
                continue;
            }
        }

        trimInPlace(buf);
        return;
    }
}

void readNonEmpty(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        readLine(prompt, buf, size);
        if (strlen(buf) == 0) {
            printf("This field cannot be empty.\n");
        } else {
            return;
        }
    }
}

int readInt(const char *prompt, int min, int max)
{
    char line[64];

    for (;;) {
        readLine(prompt, line, sizeof line);
        if (strlen(line) == 0) {
            printf("Input cannot be empty.\n");
            continue;
        }

        char *end;
        errno = 0;
        long value = strtol(line, &end, 10);

        if (*end != '\0' || errno == ERANGE) {
            printf("Invalid input. Please enter a whole number.\n");
        } else if (value < min || value > max) {
            printf("Please enter a number between %d and %d.\n", min, max);
        } else {
            return (int)value;
        }
    }
}

double readMoney(const char *prompt)
{
    char line[64];

    for (;;) {
        readLine(prompt, line, sizeof line);
        if (strlen(line) == 0) {
            printf("Input cannot be empty.\n");
            continue;
        }

        /* only digits, one decimal point and an optional leading minus are allowed */
        int ok = 1;
        int dots = 0;
        for (size_t i = 0; i < strlen(line); i++) {
            char c = line[i];
            if (c == '.') {
                dots++;
            } else if (!isdigit((unsigned char)c) && !(i == 0 && c == '-')) {
                ok = 0;
            }
        }

        char *end;
        double value = strtod(line, &end);

        if (!ok || dots > 1 || end == line || *end != '\0') {
            printf("Invalid amount. Use digits only, for example 12500.50\n");
        } else if (value < 0) {
            printf("Amount cannot be negative.\n");
        } else if (value > MAX_MONEY) {
            printf("Amount is too large.\n");
        } else {
            return value;
        }
    }
}

int readMenuChoice(const char *prompt, int min, int max)
{
    char line[64];

    for (;;) {
        readLine(prompt, line, sizeof line);

        char *end;
        long value = strtol(line, &end, 10);

        if (strlen(line) == 0 || *end != '\0' || value < min || value > max) {
            printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
        } else {
            return (int)value;
        }
    }
}

int isValidEmail(const char *email)
{
    size_t len = strlen(email);
    const char *at = strchr(email, '@');

    if (len < 5 || at == NULL || at == email) {
        return 0;
    }
    if (strchr(at + 1, '@') != NULL) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        if (isspace((unsigned char)email[i])) {
            return 0;
        }
    }
    const char *dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || dot[1] == '\0') {
        return 0;
    }
    return 1;
}

int isValidPhone(const char *phone)
{
    size_t len = strlen(phone);
    int digits = 0;

    if (len < 7) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        char c = phone[i];
        if (isdigit((unsigned char)c)) {
            digits++;
        } else if (!(c == ' ' || c == '-' || (c == '+' && i == 0))) {
            return 0;
        }
    }
    return digits >= 7;
}

void readEmail(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        readNonEmpty(prompt, buf, size);
        if (isValidEmail(buf)) {
            return;
        }
        printf("Invalid email address (example: name@example.com).\n");
    }
}

void readPhone(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        readNonEmpty(prompt, buf, size);
        if (isValidPhone(buf)) {
            return;
        }
        printf("Invalid phone number (at least 7 digits; digits, spaces, '-' and a leading '+' only).\n");
    }
}

void toLowerStr(char *dest, const char *src, size_t size)
{
    size_t n = strlen(src);
    if (n > size - 1) {
        n = size - 1;
    }
    for (size_t i = 0; i < n; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[n] = '\0';
}

/* Case-insensitive equality: both strings are lower-cased, then compared with strcmp. */
int equalsIgnoreCase(const char *a, const char *b)
{
    char la[128];
    char lb[128];

    toLowerStr(la, a, sizeof la);
    toLowerStr(lb, b, sizeof lb);
    return strcmp(la, lb) == 0;
}

/* Case-insensitive "does text contain keyword?" */
int containsIgnoreCase(const char *text, const char *keyword)
{
    size_t n = strlen(text);
    size_t m = strlen(keyword);

    if (m == 0) {
        return 1;
    }
    if (m > n) {
        return 0;
    }
    for (size_t i = 0; i + m <= n; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)keyword[j])) {
                break;
            }
        }
        if (j == m) {
            return 1;
        }
    }
    return 0;
}
