#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "account.h"
#include <time.h>

int transactionCounter = 1;

void saveTransaction(char message[])
{
    printf("\n SAVE FUNCTION WORKING\n");

    FILE *fp = fopen("transactions.txt", "a");

    if(fp == NULL)
        return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

fprintf(fp,
        "[TXN-%04d] [%02d-%02d-%04d %02d:%02d:%02d] %s\n",
        transactionCounter++,
        t->tm_mday,
        t->tm_mon + 1,
        t->tm_year + 1900,
        t->tm_hour,
        t->tm_min,
        t->tm_sec,
        message);

    fclose(fp);

    printf("Transaction saved with timestamp!\n");
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
        "Transfer | From: %d (%s) | To: %d (%s) | Amount: %.2f",
        accounts[senderIndex].accountNumber,
        accounts[senderIndex].name,
        accounts[receiverIndex].accountNumber,
        accounts[receiverIndex].name,
        amount);

saveTransaction(log);
    printf("\nTransfer Successful!\n");
    printf("%.2f transferred successfully.\n", amount);
}