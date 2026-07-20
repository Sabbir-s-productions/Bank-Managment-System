#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "account.h"
#include "transaction.h"
#include "admin.h"
#include "loan.h"
#include "fd.h"
#include "card.h"

void restoreDatabase();
void saveTransaction(char message[]);
void viewTransactions();
void transferMoney();
void dashboard();
void changeAdminPassword();
void createDefaultPassword();
void login();
void customerLogin();
void unlockAccount();
void searchTransactionByAccount();

int isDuplicateAccount(int accNo);







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

int main()
{
    createDefaultPassword();

int role;

printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
printf("1. Admin Login\n");
printf("2. Customer Login\n");
printf("3. Exit\n");

printf("Enter Choice: ");
scanf("%d", &role);

if(role == 1)
{
    login();
    dashboard();
}
else if(role == 2)
{
    customerLogin();
    return 0;
}
else
{
    return 0;
}

    int choice;

    while(1)
    {
        title();

  
        printf("1. Create Account\n");
        printf("2. View Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Check Balance\n");
        printf("7. Delete Account\n");
        printf("8. Change PIN\n");
        printf("9. Search by Name\n");
        printf("10. Bank Statistics\n");
        printf("11. Top 5 Richest Customers\n");
        printf("12. Account Report\n");
        printf("13. Transfer Money\n");
        printf("14. View Transaction History\n");
        printf("15. Change Admin Password\n");
        printf("16. Export to CSV\n");
        printf("17. Backup Database\n");
        printf("18. Restore Database\n");
        printf("19. Generate Account Statement\n");
        printf("20. Apply for Loan\n");
        printf("21. View Loan Requests\n");
        printf("22. Approve Loan\n");
        printf("23. Reject Loan\n");
        printf("24. Unlock Account\n");
        printf("25. Create Fixed Deposit\n");
        printf("26. View All Fixed Deposits\n");
        printf("27. Search Transactions by Account\n");
        printf("28. Edit Account Information\n");
        printf("29. Create ATM Card\n");
        printf("30. View ATM Cards\n");
        printf("31. Block ATM Card\n");
        printf("32. Unblock ATM Card\n");
        printf("33. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            createAccount();
        }
        else if(choice == 2)
        {
            viewAccounts();
        }
        else if(choice == 3)
        {
            searchAccount();
        }
        else if(choice == 4)
        {
            depositMoney();
        }
        else if(choice == 5)
        {
            withdrawMoney();
        }
        else if(choice == 6)
        {
            checkBalance();
        }
        else if(choice == 7)
        {
            deleteAccount();
        }
        else if(choice == 8)
        {
            changePIN();
        }
        else if(choice == 9)
        {
            searchByName();
        }
        else if(choice == 10)
        {
            bankStatistics();
        }
        else if(choice == 11)
        {
            top5Customers();
        }
        else if(choice == 12)
        {
            accountReport();
        }
        else if(choice == 13)
        {
            transferMoney();
        }
        else if(choice == 14)
        {
            viewTransactions();
        }
        else if(choice == 15)
        {
            changeAdminPassword();
        }
        else if(choice == 16)
        {
            exportCSV();
        }
        else if(choice == 17)
        {
            backupDatabase();
        }
        else if(choice == 18)
        {
            restoreDatabase();
        }
        else if(choice == 19)
        {
            generateStatement();
        }
        else if(choice == 20)
        {
            applyLoan();
        }
        else if(choice == 21)
        {
            viewLoans();
        }
        else if(choice == 22)
        {
            approveLoan();
        }
        else if(choice == 23)
        {
            rejectLoan();
        }
        else if(choice == 24)
        {
            unlockAccount();
        }
        else if(choice == 25)
        {
            createFixedDeposit();
        }
        else if(choice == 26)
        {
            viewFDs();
        }
        else if(choice == 27)
        {
            searchTransactionByAccount();
        }
        else if(choice == 28)
        {
            editAccount();
        }
else if(choice == 29)
{
    createATMCard();
}
else if(choice == 30)
{
    viewATMCards();
}
else if(choice == 31)
{
    blockATMCard();
}
else if(choice == 32)
{
    unblockATMCard();
}
else if(choice == 33)
{
    printf("\n=================================\n");
    printf("Thank You For Using Bank Management System\n");
    printf("=================================\n");
    break;
}
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}