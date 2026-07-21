#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "account.h"
#include "transaction.h"
#include "card.h"

void atmWithdraw(int accountNumber);

typedef struct
{
    int accountNumber;
    long long cardNumber;
    int cvv;
    int expiryYear;
    int cardPIN;
    int isBlocked;
} ATMCard;


void createATMCard()
{
    FILE *fp = fopen("cards.dat", "ab");

    if(fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    ATMCard card;

    printf("Enter Account Number: ");
    scanf("%d", &card.accountNumber);

    srand(time(NULL));

    card.cardNumber =
        1000000000000000LL + rand();

    card.cvv =
        100 + rand() % 900;

    card.expiryYear = 2031;

    printf("Set 4-Digit ATM PIN: ");
scanf("%d", &card.cardPIN);

if(card.cardPIN < 1000 || card.cardPIN > 9999)
{
    printf("PIN Must Be 4 Digits!\n");
    fclose(fp);
    return;
}

    card.isBlocked = 0;

    fwrite(&card, sizeof(ATMCard), 1, fp);

    fclose(fp);

    printf("\nATM Card Created Successfully!\n");
    printf("Card Number : %I64d\n", card.cardNumber);
    printf("CVV         : %d\n", card.cvv);
    printf("Expiry Year : %d\n", card.expiryYear);
}

void viewATMCards()
{
    FILE *fp = fopen("cards.dat", "rb");

    if(fp == NULL)
    {
        printf("No ATM Cards Found!\n");
        return;
    }

    ATMCard card;

    printf("\n========== ATM CARDS ==========\n");

    while(fread(&card, sizeof(ATMCard), 1, fp))
    {
        printf("\nAccount Number : %d\n", card.accountNumber);
        printf("Card Number    : %I64d\n", card.cardNumber);
        printf("CVV            : %d\n", card.cvv);
        printf("Expiry Year    : %d\n", card.expiryYear);
        printf("Status         : %s\n",
               card.isBlocked ? "BLOCKED" : "ACTIVE");

        printf("--------------------------------\n");
    }

    fclose(fp);
}

void blockATMCard()
{
    FILE *fp = fopen("cards.dat", "rb+");

    if(fp == NULL)
    {
        printf("No ATM Cards Found!\n");
        return;
    }

    long long cardNo;
    ATMCard card;
    int found = 0;

    printf("Enter Card Number: ");
    scanf("%I64d", &cardNo);

    while(fread(&card, sizeof(ATMCard), 1, fp))
    {
        if(card.cardNumber == cardNo)
        {
            card.isBlocked = 1;

            fseek(fp, -sizeof(ATMCard), SEEK_CUR);
            fwrite(&card, sizeof(ATMCard), 1, fp);

            printf("ATM Card Blocked Successfully!\n");

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Card Not Found!\n");
    }
}

void unblockATMCard()
{
    FILE *fp = fopen("cards.dat", "rb+");

    if(fp == NULL)
    {
        printf("No ATM Cards Found!\n");
        return;
    }

    long long cardNo;
    ATMCard card;
    int found = 0;

    printf("Enter Card Number: ");
    scanf("%I64d", &cardNo);
    while(fread(&card, sizeof(ATMCard), 1, fp))
    {
        if(card.cardNumber == cardNo)
        {
            card.isBlocked = 0;

            fseek(fp, -sizeof(ATMCard), SEEK_CUR);
            fwrite(&card, sizeof(ATMCard), 1, fp);

            printf("ATM Card Unblocked Successfully!\n");

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Card Not Found!\n");
    }
}

void atmLogin()
{
    FILE *fp = fopen("cards.dat", "rb");

    if(fp == NULL)
    {
        printf("No ATM Cards Found!\n");
        return;
    }

    long long cardNo;
    int pin;

    ATMCard card;
    int found = 0;

    printf("\n===== ATM LOGIN =====\n");

    printf("Card Number: ");
    scanf("%I64d", &cardNo);

    printf("PIN: ");
    scanf("%d", &pin);

    while(fread(&card, sizeof(ATMCard), 1, fp))
    {
        if(card.cardNumber == cardNo)
        {
            found = 1;

            if(card.isBlocked)
            {
                printf("ATM Card Is Blocked!\n");
                fclose(fp);
                return;
            }

            if(card.cardPIN == pin)
            {
                printf("\nATM Login Successful!\n");
                printf("Account Number : %d\n",
                       card.accountNumber);

                int choice;

                while(1)
                {
                    printf("\n===== ATM MENU =====\n");
                    printf("1. Check Balance\n");
                    printf("2. Cash Withdraw\n");
                    printf("3. Mini Statement\n");
                    printf("4. Change ATM PIN\n");
                    printf("5. Exit ATM\n");

                    printf("Enter Choice: ");
                    scanf("%d", &choice);

                    if(choice == 1)
                    {
                        FILE *afp = fopen("accounts.dat", "rb");

                        if(afp != NULL)
                        {
                            Account a;

                            while(fread(&a, sizeof(Account), 1, afp))
                            {
                                if(a.accountNumber == card.accountNumber)
                                {
                                    printf("Current Balance: %.2f\n",
                                           a.balance);
                                    break;
                                }
                            }

                            fclose(afp);
                        }
                    }

                    else if(choice == 2)
{
    atmWithdraw(card.accountNumber);
}
                    else if(choice == 3)
                    {
                        FILE *tf = fopen("transactions.txt", "r");

                        if(tf == NULL)
                        {
                            printf("No Transactions Found!\n");
                        }
                        else
                        {
                            char line[500];
                            char accStr[50];

                            sprintf(accStr,
                                    "Account: %d",
                                    card.accountNumber);

                            printf("\n===== MINI STATEMENT =====\n");

                            while(fgets(line,
                                        sizeof(line),
                                        tf))
                            {
                                if(strstr(line, accStr))
                                {
                                    printf("%s", line);
                                }
                            }

                            fclose(tf);
                        }
                    }
                    else if(choice == 4)
                    {
                        changeATMPIN();
                    }
                    else if(choice == 5)
                    {
                        printf("ATM Session Ended!\n");
                        break;
                    }
                    else
                    {
                        printf("Invalid Choice!\n");
                    }
                }
            }

            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Card Not Found!\n");
    }
}

void atmWithdraw(int accountNumber)
{
    FILE *fp = fopen("accounts.dat", "rb+");

    if(fp == NULL)
    {
        printf("Account File Not Found!\n");
        return;
    }

    float amount;
    Account a;

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if(amount <= 0)
    {
        printf("Invalid Amount!\n");
        fclose(fp);
        return;
    }

    while(fread(&a, sizeof(Account), 1, fp))
    {
        if(a.accountNumber == accountNumber)
        {
            if(a.balance < amount)
            {
                printf("Insufficient Balance!\n");
                fclose(fp);
                return;
            }

            a.balance -= amount;

            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, fp);

            char log[200];

            sprintf(log,
                    "ATM Withdraw | Account: %d | Amount: %.2f",
                    a.accountNumber,
                    amount);

            saveTransaction(log);

            printf("Cash Withdraw Successful!\n");
            printf("Remaining Balance: %.2f\n", a.balance);

            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

void changeATMPIN()
{
    FILE *fp = fopen("cards.dat", "rb+");

    if(fp == NULL)
    {
        printf("No ATM Cards Found!\n");
        return;
    }

    long long cardNo;
    int oldPIN, newPIN;
    ATMCard card;
    int found = 0;

    printf("Enter Card Number: ");
    scanf("%I64d", &cardNo);

    printf("Enter Current PIN: ");
    scanf("%d", &oldPIN);

    while(fread(&card, sizeof(ATMCard), 1, fp))
    {
        if(card.cardNumber == cardNo)
        {
            found = 1;

            if(card.cardPIN != oldPIN)
            {
                printf("Incorrect Current PIN!\n");
                fclose(fp);
                return;
            }

            printf("Enter New PIN: ");
            scanf("%d", &newPIN);

            if(newPIN < 1000 || newPIN > 9999)
            {
                printf("PIN Must Be 4 Digits!\n");
                fclose(fp);
                return;
            }

            card.cardPIN = newPIN;

            fseek(fp, -sizeof(ATMCard), SEEK_CUR);
            fwrite(&card, sizeof(ATMCard), 1, fp);

            printf("ATM PIN Changed Successfully!\n");

            fclose(fp);
            return;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Card Not Found!\n");
    }
}