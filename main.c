#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int accountNumber;
    char name[100];
    int pin;
    float balance;
} Account;

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

    printf("Account Holder Name: ");
    scanf(" %[^\n]", a.name);

    printf("PIN (4 digits): ");
    scanf("%d", &a.pin);

    printf("Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(Account), 1, fp);

    fclose(fp);

    printf("\nAccount Created Successfully!\n");
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
        printf("PIN            : %d\n", a.pin);
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
            printf("\nAccount Found!\n");
            printf("Account Number : %d\n", a.accountNumber);
            printf("Name           : %s\n", a.name);
            printf("Balance        : %.2f\n", a.balance);

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

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accNo)
        {
            a.balance += amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);

            fwrite(&a, sizeof(Account), 1, fp);

            printf("\nDeposit Successful!\n");
            printf("New Balance: %.2f\n", a.balance);

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

            printf("\nWithdrawal Successful!\n");
            printf("Remaining Balance: %.2f\n", a.balance);

            break;
        }
    }

    if(found == 0)
    {
        printf("Account Not Found!\n");
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
int main()
{
    int choice;

    while(1)
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. View Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Check Balance\n");
        printf("7. Delete Account\n");
        printf("8. Change PIN\n");
        printf("9. Exit\n");

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
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}