#ifndef VALIDATION_H
#define VALIDATION_H

int getMenuChoice(int min, int max);
float getPositive(const char *prompt);
int getPositiveInteger(const char *prompt);
int isEmptyString(const char *text);
void getString(const char *prompt,
char *value, int size);

#endif