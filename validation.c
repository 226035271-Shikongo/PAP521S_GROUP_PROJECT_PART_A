#include <stdio.h>
#include <string.h>
#include validation.h

int getMenuChoice(int min, int max)
{
    int choice;
    while(1)
    { printf("Enter your choice:");
    if(scanf("%d",&choice) !=1){
        printf("Invalid input. Please enter a number \n");
        while (getchar() != '\n');
        continue;
    
    }
    while(getchar() != '\n');
    if(choice >= min  && choice <= max){
      return choice;
    }
    printf("Invalid choice. Please enter a number between %d and %d \n", min, max);
    }

 }

 float getPositiveAmount(const char *prompt)
 {
     float amount;
     while(1)
     {
         printf("%s", prompt);
         if(scanf("%f", &amount) != 1)
         {
             printf("Invalid input. Please enter a number.\n");
             while(getchar() != '\n');
             continue;
         }
         while(getchar() != '\n');
         if(amount >= 0)
         {
             return amount;
         }
         printf("This value can't be negative. Please try again.\n");
     }
 }

int getPositiveInteger(const char *prompt)
{
    int number;
    while(1)
    {
        printf("%s", prompt);
        if(scanf("%d", &number) != 1)
        {
            printf("Invalid input. Please enter a whole number.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        if(number >= 0)
        {
            return number;
        }
        printf("This number can't be negative. Please try again.\n");
    }
}

int isEmptyString(const char *text)
{ if (text == NULL)
{
    return 1;
}
return strlen(text) == 0;
}

void getString(const char *prompt, char *value, int size)
{
    while(1)
    {
        printf("%s", prompt);
        if(fgets(value, size, stdin) == NULL)
        {
             value[strcspn(value, "\n")] = '\0';
          if (! isEmptyString(value))
        { return;
        }
        }
              printf("Input cannot be empty. Please try again.\n");
              continue; 
    }
    
 }
