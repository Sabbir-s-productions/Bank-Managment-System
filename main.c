#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

void restoreDatabase();
void saveTransaction(char message[]);
void viewTransactions();
void transferMoney();
void dashboard();
void changeAdminPassword();
void createDefaultPassword();
void login();
void customerLogin();

int isDuplicateAccount(int accNo);

typedef struct
{
    int accountNumber;
    char name[100];
    int pin;
    float balance;
    char accountType[20];
} Account;

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

    printf("Initial Balance: ");
    scanf("%f", &a.balance);

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
        "Deposit | Account: %d | Amount: %.2f",
        a.accountNumber,
        amount);

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
        "Withdraw | Account: %d | Amount: %.2f",
        a.accountNumber,
        amount);

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
            if(a.balance > 0)
                printf("Status         : ACTIVE\n");
            else
                printf("Status         : INACTIVE\n");

            printf("====================================\n");

            break;
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

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

void saveTransaction(char message[])
{
    FILE *fp = fopen("transactions.txt", "a");

    if(fp == NULL)
        return;

    fprintf(fp, "%s\n", message);

    fclose(fp);
}
void transferMoney()
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Account Data Found!\n");
        return;
    }

    int senderAcc, receiverAcc;
    float amount;

    printf("Enter Sender Account Number: ");
    scanf("%d", &senderAcc);

    printf("Enter Receiver Account Number: ");
    scanf("%d", &receiverAcc);

    printf("Enter Amount: ");
    scanf("%f", &amount);

    Account accounts[1000];
    int n = 0;

    while(fread(&accounts[n], sizeof(Account), 1, fp))
    {
        n++;
    }

    int senderIndex = -1;
    int receiverIndex = -1;

    for(int i = 0; i < n; i++)
    {
        if(accounts[i].accountNumber == senderAcc)
            senderIndex = i;

        if(accounts[i].accountNumber == receiverAcc)
            receiverIndex = i;
    }

    if(amount <= 0)
{
    printf("Invalid Amount!\n");
    fclose(fp);
    return;
}

    if(senderIndex == -1)
    {
        printf("Sender Account Not Found!\n");
        fclose(fp);
        return;
    }

    if(receiverIndex == -1)
    {
        printf("Receiver Account Not Found!\n");
        fclose(fp);
        return;
    }

    if(accounts[senderIndex].balance < amount)
    {
        printf("Insufficient Balance!\n");
        fclose(fp);
        return;
    }

    accounts[senderIndex].balance -= amount;
    accounts[receiverIndex].balance += amount;

    rewind(fp);

    for(int i = 0; i < n; i++)
    {
        fwrite(&accounts[i], sizeof(Account), 1, fp);
    }

    fclose(fp);

    char log[200];

sprintf(log,
        "Transfer | From: %d | To: %d | Amount: %.2f",
        senderAcc,
        receiverAcc,
        amount);

saveTransaction(log);
    printf("\nTransfer Successful!\n");
    printf("%.2f transferred successfully.\n", amount);
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

void viewTransactions()
{
    FILE *fp = fopen("transactions.txt", "r");

    if(fp == NULL)
    {
        printf("No Transaction History Found!\n");
        return;
    }

    char line[300];

    printf("\n========== TRANSACTION HISTORY ==========\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    printf("=========================================\n");

    fclose(fp);
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

void customerLogin()
{
    FILE *fp = fopen("accounts.dat", "rb");

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
        if(a.accountNumber == accNo && a.pin == pin)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Invalid Account Number or PIN!\n");
        return;
    }

    printf("\nWelcome %s\n", a.name);

    int choice;

    while(1)
    {
        printf("\n===== CUSTOMER PANEL =====\n");
        printf("1. Check Balance\n");
        printf("2. Logout\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("Current Balance: %.2f\n", a.balance);
        }
        else if(choice == 2)
        {
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
        printf("19. Exit\n");

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
            printf("\n=================================\n");
    printf("Thank You For Using Bank Management System\n");
    printf("=================================\n");

    break;
        }
        else
        {
            printf("Invalid Choice!\n");

            break;
        }
    }

    return 0;
}