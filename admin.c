#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "account.h"
#include "ui.h"

void createDefaultPassword()
{
    FILE *fp = fopen("admin.dat", "rb");

    if(fp == NULL)
    {
        char password[50] = "admin123";

        fp = fopen("admin.dat", "wb");
        fwrite(password, sizeof(password), 1, fp);
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }
}

void login()
{
    char savedPass[50];
    char inputPass[50];

    FILE *fp = fopen("admin.dat", "rb");

    fread(savedPass, sizeof(savedPass), 1, fp);
    fclose(fp);

    printf("\n========== LOGIN ==========\n");
    printf("Enter Admin Password: ");
    scanf("%s", inputPass);

    if(strcmp(savedPass, inputPass) != 0)
    {
        printf("Wrong Password!\n");
        exit(0);
    }

    printf("\nLogin Successful!\n");
}

void changeAdminPassword()
{
    char oldPass[50];
    char savedPass[50];
    char newPass[50];

    FILE *fp = fopen("admin.dat", "rb");

    if(fp == NULL)
    {
        printf("Password File Error!\n");
        return;
    }

    fread(savedPass, sizeof(savedPass), 1, fp);
    fclose(fp);

    printf("Enter Current Password: ");
    scanf("%s", oldPass);

    if(strcmp(oldPass, savedPass) != 0)
    {
        printf("Incorrect Password!\n");
        return;
    }

    printf("Enter New Password: ");
    scanf("%s", newPass);

    fp = fopen("admin.dat", "wb");

    fwrite(newPass, sizeof(newPass), 1, fp);

    fclose(fp);

    printf("\nPassword Changed Successfully!\n");
}

void dashboard()
{
    FILE *fp = fopen("accounts.dat", "rb");

    int totalAccounts = 0;
    float totalBalance = 0;

    if(fp != NULL)
    {
        Account a;

        while(fread(&a, sizeof(Account), 1, fp))
        {
            totalAccounts++;
            totalBalance += a.balance;
        }

        fclose(fp);
    }

   setColor(11);

printf("\n");
line();
printf("            BANK DASHBOARD\n");
line();

setColor(10);

printf("Total Accounts : %d\n", totalAccounts);
printf("Total Balance  : %.2f\n", totalBalance);

setColor(11);

line();


}

void bankStatistics()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;

    int totalAccounts = 0;
    float totalBalance = 0;

    float highestBalance = -1;
    char richestCustomer[100];

    while(fread(&a, sizeof(Account), 1, fp))
    {
        totalAccounts++;
        totalBalance += a.balance;

        if(a.balance > highestBalance)
        {
            highestBalance = a.balance;
            strcpy(richestCustomer, a.name);
        }
    }

    fclose(fp);

    printf("\n====================================\n");
    printf("        BANK STATISTICS\n");
    printf("====================================\n");

    printf("Total Accounts   : %d\n", totalAccounts);
    printf("Total Balance    : %.2f\n", totalBalance);

    if(totalAccounts > 0)
    {
        printf("Average Balance  : %.2f\n",
               totalBalance / totalAccounts);

        printf("Richest Customer : %s\n",
               richestCustomer);

        printf("Highest Balance  : %.2f\n",
               highestBalance);
    }

    printf("====================================\n");
}

void top5Customers()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account accounts[1000];
    int n = 0;

    while(fread(&accounts[n], sizeof(Account), 1, fp))
    {
        n++;
    }

    fclose(fp);

    if(n == 0)
    {
        printf("No Account Records!\n");
        return;
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(accounts[i].balance < accounts[j].balance)
            {
                Account temp = accounts[i];
                accounts[i] = accounts[j];
                accounts[j] = temp;
            }
        }
    }

    printf("\n====================================\n");
    printf("      TOP 5 RICHEST CUSTOMERS\n");
    printf("====================================\n");

    int limit = (n < 5) ? n : 5;

    for(int i = 0; i < limit; i++)
    {
        printf("%d. %s | Balance: %.2f\n",
               i + 1,
               accounts[i].name,
               accounts[i].balance);
    }

    printf("====================================\n");
}












void exportCSV()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    FILE *csv = fopen("accounts.csv", "w");

    Account a;

    fprintf(csv, "AccountNumber,Name,Balance\n");

    while(fread(&a, sizeof(Account), 1, fp))
    {
        fprintf(csv,
                "%d,%s,%.2f\n",
                a.accountNumber,
                a.name,
                a.balance);
    }

    fclose(fp);
    fclose(csv);

    printf("accounts.csv created successfully!\n");
}



void backupDatabase()
{
    FILE *src = fopen("accounts.dat", "rb");

    if(src == NULL)
    {
        printf("No Database Found!\n");
        return;
    }

    FILE *dest = fopen("backup.dat", "wb");

    Account a;

    while(fread(&a, sizeof(Account), 1, src))
    {
        fwrite(&a, sizeof(Account), 1, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Database Backup Created Successfully!\n");
}

void restoreDatabase()
{
    FILE *src = fopen("backup.dat", "rb");

    if(src == NULL)
    {
        printf("No Backup Found!\n");
        return;
    }

    FILE *dest = fopen("accounts.dat", "wb");

    Account a;

    while(fread(&a, sizeof(Account), 1, src))
    {
        fwrite(&a, sizeof(Account), 1, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Database Restored Successfully!\n");
}
