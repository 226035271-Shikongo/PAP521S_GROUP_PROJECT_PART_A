#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define MAX_ID 999999

/* Safe input helpers: every one of them re-prompts until the input is valid. */
void   readLine(const char *prompt, char *buf, size_t size);      /* any text, may be empty   */
void   readNonEmpty(const char *prompt, char *buf, size_t size);  /* text that is not empty   */
int    readInt(const char *prompt, int min, int max);             /* whole number in a range  */
double readMoney(const char *prompt);                             /* amount >= 0              */
int    readMenuChoice(const char *prompt, int min, int max);      /* menu option              */
void   readEmail(const char *prompt, char *buf, size_t size);
void   readPhone(const char *prompt, char *buf, size_t size);

/* Validation and string helpers */
int  isValidEmail(const char *email);
int  isValidPhone(const char *phone);
void toLowerStr(char *dest, const char *src, size_t size);
int  equalsIgnoreCase(const char *a, const char *b);
int  containsIgnoreCase(const char *text, const char *keyword);

#endif
