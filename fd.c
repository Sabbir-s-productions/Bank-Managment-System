#include <stdio.h>
#include <math.h>
#include "fd.h"

int getNextFDID()
{
    FILE *fp = fopen("fd.dat", "rb");

    if(fp == NULL)
    {
        return 1;
    }

    FixedDeposit fd;
    int lastID = 0;

    while(fread(&fd, sizeof(FixedDeposit), 1, fp))
    {
        lastID = fd.fdID;
    }

    fclose(fp);

    return lastID + 1;
}


void createFixedDeposit()
{
    FixedDeposit fd;
    
    float amount;
    float rate;
    int years;

    printf("\n===== FIXED DEPOSIT =====\n");

    printf("Deposit Amount: ");
    scanf("%f", &amount);

    printf("Interest Rate (%%): ");
    scanf("%f", &rate);

    printf("Years: ");
    scanf("%d", &years);

fd.amount = amount;
fd.rate = rate;
fd.years = years;

fd.maturity =
    amount * pow((1 + rate / 100), years);

    printf("\n===== FD RESULT =====\n");
    printf("Principal Amount : %.2f\n", amount);
    printf("Interest Rate    : %.2f%%\n", rate);
    printf("Years            : %d\n", years);
printf("Maturity Amount  : %.2f\n", fd.maturity);

FILE *fp = fopen("fd.dat", "ab");

if(fp != NULL)
{
    fd.fdID = getNextFDID();

    fwrite(&fd, sizeof(FixedDeposit), 1, fp);

    fclose(fp);

    printf("\nFD Saved Successfully!\n");
}
}

void viewFixedDeposits()
{
    FILE *fp = fopen("fd.dat", "rb");

    if(fp == NULL)
    {
        printf("No FD Records Found!\n");
        return;
    }

    FixedDeposit fd;

    printf("\n========== FIXED DEPOSITS ==========\n");

    while(fread(&fd, sizeof(FixedDeposit), 1, fp))
    {
        printf("\nFD ID           : %d\n", fd.fdID);
        printf("Amount          : %.2f\n", fd.amount);
        printf("Interest Rate   : %.2f%%\n", fd.rate);
        printf("Years           : %d\n", fd.years);
        printf("Maturity Amount : %.2f\n", fd.maturity);
        printf("-----------------------------------\n");
    }

    fclose(fp);
}