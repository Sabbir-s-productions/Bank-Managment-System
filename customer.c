#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"
#include "account.h"

void customerLogin()
{
   FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    int accNo, pin;
    Account a;
    int found = 0;

    printf("\n===== CUSTOMER LOGIN =====\n");

    printf("Account Number: ");
    scanf("%d", &accNo);

    printf("PIN: ");
    scanf("%d", &pin);

  while(fread(&a, sizeof(Account), 1, fp))
{
    if(a.accountNumber == accNo)
    {
        if(a.isLocked == 1)
        {
            printf("Account Locked!\n");
            fclose(fp);
            return;
        }

        if(a.pin == pin)
        {
            found = 1;
            break;
        }

        printf("Invalid PIN!\n");
        a.failedAttempts++;

if(a.failedAttempts >= 3)
{
    a.isLocked = 1;
    printf("Account Locked!\n");
}
else
{
    printf("Attempts Left: %d\n", 3 - a.failedAttempts);
}

    fseek(fp, -sizeof(Account), SEEK_CUR);
    fwrite(&a, sizeof(Account), 1, fp);
        fclose(fp);
        return;
    }
}
    fclose(fp);

    if(!found)
    {
        printf("Invalid Account Number or PIN!\n");
        return;
    }

    printf("\nWelcome %s\n", a.name);

    printf("\n====================================\n");
printf("        CUSTOMER DASHBOARD\n");
printf("====================================\n");

printf("Name           : %s\n", a.name);
printf("Account Number : %d\n", a.accountNumber);
printf("Account Type   : %s\n", a.accountType);
printf("Balance        : %.2f\n", a.balance);

printf("====================================\n");

    int choice;

    while(1)
    {
        printf("\n===== CUSTOMER PANEL =====\n");
        printf("1. Check Balance\n");
        printf("2. View My Transactions\n");
        printf("3. Change PIN\n");
        printf("4. View Profile\n");
        printf("5. Logout\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Current Balance: %.2f\n", a.balance);
        }
        else if(choice == 2)
        {
           FILE *fp = fopen("transactions.txt", "r");

if(fp == NULL)
{
    printf("No Transaction History Found!\n");
}
else
{
    char line[500];
    char accStr[50];

    sprintf(accStr, "Account: %d", a.accountNumber);

    printf("\n===== YOUR TRANSACTIONS =====\n");
    int count = 0;

    while(fgets(line, sizeof(line), fp))
    {
        if(strstr(line, accStr))
{
    printf("%s", line);

    count++;

    if(count >= 5)
        break;
}
    }

    fclose(fp);
}
        }
        else if(choice == 3)
        {
            int newPin;

printf("Enter New PIN: ");
scanf("%d", &newPin);

FILE *fp = fopen("accounts.dat", "rb+");

if(fp == NULL)
{
    printf("Error!\n");
    continue;
}

Account temp;

while(fread(&temp, sizeof(Account), 1, fp))
{
    if(temp.accountNumber == a.accountNumber)
    {
        temp.pin = newPin;

        fseek(fp, -sizeof(Account), SEEK_CUR);
        fwrite(&temp, sizeof(Account), 1, fp);

        a.pin = newPin;

        printf("PIN Changed Successfully!\n");
        break;
    }
}

fclose(fp);
        }
        else if(choice == 4)
{
    printf("\n===== CUSTOMER PROFILE =====\n");

    printf("Name           : %s\n", a.name);
    printf("Account Number : %d\n", a.accountNumber);
    printf("Balance        : %.2f\n", a.balance);
    printf("PIN            : ****\n");

    printf("============================\n");
}
else if(choice == 5)
{
    printf("Logged Out Successfully!\n");
    break;
}
        else
        {
            printf("Invalid Choice!\n");
        }
       
      
    }
}