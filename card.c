#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int accountNumber;
    long long cardNumber;
    int cvv;
    int expiryYear;
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

    card.isBlocked = 0;

    fwrite(&card, sizeof(ATMCard), 1, fp);

    fclose(fp);

    printf("\nATM Card Created Successfully!\n");
    printf("Card Number : %lld\n", card.cardNumber);
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
        printf("Card Number    : %lld\n", card.cardNumber);
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
    scanf("%lld", &cardNo);

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
    scanf("%lld", &cardNo);

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