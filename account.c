#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "account.h"
#include "ui.h"
#include "transaction.h"

int isDuplicateAccount(int accNo)
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        return 0;
    }

    Account a;

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void createAccount()
{
    FILE *fp = fopen("accounts.dat", "ab");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    Account a;

    printf("Account Number: ");
    scanf("%d", &a.accountNumber);

    if(isDuplicateAccount(a.accountNumber))
    {
        printf("Account Number Already Exists!\n");
        fclose(fp);
        return;
    }

    printf("Account Type (Savings/Current): ");
scanf("%s", a.accountType);

    printf("Account Holder Name: ");
    scanf(" %[^\n]", a.name);

    printf("PIN (4 digits): ");
    scanf("%d", &a.pin);

    if(a.pin < 1000 || a.pin > 9999)
{
    printf("PIN Must Be 4 Digits!\n");
    fclose(fp);
    return;
}

    printf("Initial Balance: ");
    scanf("%f", &a.balance);

    a.failedAttempts = 0;
a.isLocked = 0;
a.isActive = 1;

    printf("Account Type : %s\n", a.accountType);

    fwrite(&a, sizeof(Account), 1, fp);

    fclose(fp);

setColor(10);
printf("\n[SUCCESS] Account Created Successfully!\n");
setColor(7);

}

void viewAccounts()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;

    printf("\n========== ALL ACCOUNTS ==========\n");

    while(fread(&a, sizeof(Account), 1, fp))
    {
        printf("\nAccount Number : %d\n", a.accountNumber);
        printf("Name           : %s\n", a.name);  
        printf("Account Type   : %s\n", a.accountType);    
        printf("Balance        : %.2f\n", a.balance);
        printf("Status         : %s\n",
       a.isLocked ? "LOCKED" : "ACTIVE");
        printf("-------------------------------\n");
    }

    fclose(fp);
}

void searchAccount()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int searchAccountNumber;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &searchAccountNumber);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == searchAccountNumber)
        {
            accountCard();

printf("Account Number : %d\n", a.accountNumber);
printf("Name           : %s\n", a.name);
printf("Account Type   : %s\n", a.accountType);
printf("Balance        : %.2f\n", a.balance);

line();

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void depositMoney()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

        if(amount <= 0)
{
    printf("Invalid Amount!\n");
    fclose(fp);
    return;
}

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            a.balance += amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);

            fwrite(&a, sizeof(Account), 1, fp);

            char log[200];

sprintf(log,
        "Deposit | Account: %d | Name: %s | Amount: %.2f | Balance: %.2f",
        a.accountNumber,
        a.name,
        amount,
        a.balance);
saveTransaction(log);
            setColor(10);
printf("\nDeposit Successful!\n");
setColor(7);
            printf("New Balance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }



    if(found == 0)
    {
        setColor(12);
printf("Account Not Found!\n");
setColor(7);
    }

    fclose(fp);
}

void withdrawMoney()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int accNo;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Withdraw Amount: ");
    scanf("%f", &amount);

        if(amount <= 0)
{
    printf("Invalid Amount!\n");
    fclose(fp);
    return;
}


    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            if(amount > a.balance)
            {
                printf("\nInsufficient Balance!\n");
                break;
            }

            a.balance -= amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);

            fwrite(&a, sizeof(Account), 1, fp);

            char log[200];

sprintf(log,
        "Withdraw | Account: %d | Name: %s | Amount: %.2f | Balance: %.2f",
        a.accountNumber,
        a.name,
        amount,
        a.balance);

saveTransaction(log);
            setColor(10);
printf("\nWithdrawal Successful!\n");
setColor(7);
            printf("Remaining Balance: %.2f\n", a.balance);

            break;
        }
    }


    if(found == 0)
    {
        setColor(12);
printf("Account Not Found!\n");
setColor(7);
    }

    fclose(fp);
}

void checkBalance()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int accNo;
    int pin;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter PIN: ");
    scanf("%d", &pin);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            if(a.pin == pin)
            {
                printf("\nAccess Granted!\n");
                printf("Current Balance: %.2f\n", a.balance);
            }
            else
            {
                printf("\nIncorrect PIN!\n");
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void deleteAccount()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");

    Account a;
    int accNo;
    int found = 0;

    printf("Enter Account Number to Delete: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;
            continue;
        }

        fwrite(&a, sizeof(Account), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if(found)
    {
        printf("\nAccount Deleted Successfully!\n");
    }
    else
    {
        printf("\nAccount Not Found!\n");
    }
}

void changePIN()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int accNo, oldPIN, newPIN;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Current PIN: ");
    scanf("%d", &oldPIN);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            if(a.pin == oldPIN)
            {
                printf("Enter New PIN: ");
                scanf("%d", &newPIN);

                a.pin = newPIN;

                fseek(fp, -sizeof(Account), SEEK_CUR);
                fwrite(&a, sizeof(Account), 1, fp);

                printf("\nPIN Changed Successfully!\n");
            }
            else
            {
                printf("\nIncorrect PIN!\n");
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void searchByName()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    char searchName[100];
    int found = 0;

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", searchName);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(strcmp(a.name, searchName) == 0)
        {
            printf("\nAccount Found!\n");
            printf("Account Number : %d\n", a.accountNumber);
            printf("Name           : %s\n", a.name);
            printf("Balance        : %.2f\n", a.balance);
            printf("----------------------------\n");

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("No Account Found!\n");
    }

    fclose(fp);
}

void accountReport()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    int accNo;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            printf("\n====================================\n");
            printf("         ACCOUNT REPORT\n");
            printf("====================================\n");

            accountCard();

printf("Account Number : %d\n", a.accountNumber);
printf("Name           : %s\n", a.name);
printf("Account Type   : %s\n", a.accountType);
printf("Balance        : %.2f\n", a.balance);

if(a.balance > 0)
    printf("Status         : ACTIVE\n");
else
    printf("Status         : INACTIVE\n");

line();
            
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void generateStatement()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    int accNo;
    Account a;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            printf("\n====================================\n");
            printf("        ACCOUNT STATEMENT\n");
            printf("====================================\n");

            printf("Name           : %s\n", a.name);
            printf("Account Number : %d\n", a.accountNumber);
            printf("Balance        : %.2f\n", a.balance);
            char filename[50];

sprintf(filename,
        "statement_%d.txt",
        a.accountNumber);

FILE *sf = fopen(filename, "w");

if(sf != NULL)
{
    fprintf(sf, "====================================\n");
    fprintf(sf, "        ACCOUNT STATEMENT\n");
    fprintf(sf, "====================================\n");

    fprintf(sf, "Name           : %s\n", a.name);
    fprintf(sf, "Account Number : %d\n", a.accountNumber);
    fprintf(sf, "Balance        : %.2f\n", a.balance);

    fclose(sf);

    printf("\nStatement exported to %s\n", filename);
}
            printf("\nRecent Transactions:\n");
printf("------------------------------------\n");

FILE *tf = fopen("transactions.txt", "r");

if(tf != NULL)
{
    char line[500];
    char accStr[50];

    sprintf(accStr, "Account: %d", a.accountNumber);

    while(fgets(line, sizeof(line), tf))
    {
        if(strstr(line, accStr))
        {
            printf("%s", line);
        }
    }

    fclose(tf);
}

            printf("====================================\n");

            break;
        }
    }

    if(!found)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void unlockAccount()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    int accNo;
    Account a;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            a.isLocked = 0;
            a.failedAttempts = 0;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, fp);

            printf("\nAccount Unlocked Successfully!\n");
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Account Not Found!\n");
    }
}

void editAccount()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    int accNo;
    Account a;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            found = 1;

            int choice;

            printf("\n===== EDIT ACCOUNT =====\n");
            printf("1. Change Name\n");
            printf("2. Change Account Type\n");
            printf("3. Reset PIN\n");

            printf("Enter Choice: ");
            scanf("%d", &choice);

            if(choice == 1)
            {
                printf("Enter New Name: ");
                scanf(" %[^\n]", a.name);
            }
            else if(choice == 2)
            {
                printf("Enter New Account Type: ");
                scanf("%s", a.accountType);
            }
            else if(choice == 3)
            {
                printf("Enter New PIN: ");
                scanf("%d", &a.pin);
            }
            else
            {
                printf("Invalid Choice!\n");
                fclose(fp);
                return;
            }

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, fp);

            printf("Account Updated Successfully!\n");
            break;
        }
    }

    if(!found)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

void applyInterest()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;
    float rate;

    printf("Enter Interest Rate (%%): ");
    scanf("%f", &rate);

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(strcmp(a.accountType, "Savings") == 0)
        {
            float interest =
                (a.balance * rate) / 100;

            a.balance += interest;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, fp);

            fseek(fp, 0, SEEK_CUR);
        }
    }

    fclose(fp);

    printf("Interest Applied Successfully!\n");
}

void monthlyRevenueReport()
{
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    Account a;

    int totalAccounts = 0;
    float totalDeposits = 0;

    while(fread(&a, sizeof(Account), 1, fp))
    {
        totalAccounts++;
        totalDeposits += a.balance;
    }

    fclose(fp);

    printf("\n===== MONTHLY BANK REPORT =====\n");
    printf("Total Accounts : %d\n", totalAccounts);
    printf("Total Deposits : %.2f\n", totalDeposits);

    printf("Estimated Monthly Revenue : %.2f\n",
           totalDeposits * 0.01);

    printf("===============================\n");
}