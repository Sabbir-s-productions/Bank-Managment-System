#include <stdio.h>
#include "loan.h"

void applyLoan()
{
    FILE *fp = fopen("loans.dat", "ab");

    if(fp == NULL)
    {
        printf("Error creating loan file!\n");
        return;
    }

    Loan l;

    printf("Account Number: ");
    scanf("%d", &l.accountNumber);

    printf("Customer Name: ");
    scanf(" %[^\n]", l.name);

    printf("Loan Amount: ");
    scanf("%f", &l.amount);

    l.approved = 0;

    fwrite(&l, sizeof(Loan), 1, fp);

    fclose(fp);

    printf("\nLoan Request Submitted Successfully!\n");
    printf("Status: Pending Approval\n");
}
void viewLoans()
{
    FILE *fp = fopen("loans.dat", "rb");

    if(fp == NULL)
    {
        printf("No Loan Requests Found!\n");
        return;
    }

    Loan l;

    while(fread(&l, sizeof(Loan), 1, fp))
    {
        printf("Account Number : %d\n", l.accountNumber);
        printf("Customer Name  : %s\n", l.name);
        printf("Loan Amount    : %.2f\n", l.amount);

     if(l.approved == 0)
{
    printf("Status: Pending\n");
}
else if(l.approved == 1)
{
    printf("Status: Approved\n");
}
else if(l.approved == -1)
{
    printf("Status: Rejected\n");
}
        printf("-----------------------------\n");
    }

    fclose(fp);
}

#include "account.h"
#include "transaction.h"

void approveLoan()
{
    FILE *lf = fopen("loans.dat", "rb+");

    if(lf == NULL)
    {
        printf("No Loan Requests Found!\n");
        return;
    }

    int accNo;
    Loan l;
    int found = 0;

    printf("Enter Account Number to Approve Loan: ");
    scanf("%d", &accNo);

    while(fread(&l, sizeof(Loan), 1, lf))
    {
        if(l.accountNumber == accNo && l.approved == 0)
        {
            found = 1;

            l.approved = 1;

            fseek(lf, -sizeof(Loan), SEEK_CUR);
            fwrite(&l, sizeof(Loan), 1, lf);

            FILE *af = fopen("accounts.dat", "rb+");

            if(af != NULL)
            {
                Account a;

                while(fread(&a, sizeof(Account), 1, af))
                {
                    if(a.accountNumber == accNo)
                    {
                        a.balance += l.amount;

                        fseek(af, -sizeof(Account), SEEK_CUR);
                        fwrite(&a, sizeof(Account), 1, af);

                        char log[200];

                        sprintf(log,
                                "Loan Approved | Account: %d | Amount: %.2f",
                                a.accountNumber,
                                l.amount);

                        saveTransaction(log);

                        printf("\nLoan Approved Successfully!\n");
                        printf("New Balance: %.2f\n", a.balance);

                        break;
                    }
                }

                fclose(af);
            }

            break;
        }
    }

    fclose(lf);

    if(!found)
    {
        printf("Pending Loan Not Found!\n");
    }
}

void rejectLoan()
{
    FILE *fp = fopen("loans.dat", "rb+");

    if(fp == NULL)
    {
        printf("No Loan Requests Found!\n");
        return;
    }

    int accNo;
    Loan l;
    int found = 0;

    printf("Enter Account Number to Reject Loan: ");
    scanf("%d", &accNo);

    while(fread(&l, sizeof(Loan), 1, fp))
    {
        if(l.accountNumber == accNo && l.approved == 0)
        {
            found = 1;

            l.approved = -1;

            fseek(fp, -sizeof(Loan), SEEK_CUR);
            fwrite(&l, sizeof(Loan), 1, fp);

            printf("\nLoan Rejected Successfully!\n");
            break;
        }
    }

    fclose(fp);

    if(!found)
    {
        printf("Pending Loan Not Found!\n");
    }
}