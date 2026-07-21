#include <stdio.h>

#include "menu.h"
#include "ui.h"

#include "account.h"
#include "transaction.h"
#include "loan.h"
#include "fd.h"
#include "card.h"
#include "admin.h"


void handleAccountMenu()
{
    int accChoice;

    while(1)
    {
        accountMenu();

        printf("Enter Choice: ");
        scanf("%d", &accChoice);

        if(accChoice == 1)
        {
            createAccount();
        }
        else if(accChoice == 2)
        {
            viewAccounts();
        }
        else if(accChoice == 3)
        {
            searchAccount();
        }
        else if(accChoice == 4)
        {
            editAccount();
        }
        else if(accChoice == 5)
        {
            deleteAccount();
        }
        else if(accChoice == 6)
        {
            checkBalance();
        }
        else if(accChoice == 7)
        {
            searchByName();
        }
        else if(accChoice == 8)
        {
            changePIN();
        }
        else if(accChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleTransactionMenu()
{
    int txnChoice;

    while(1)
    {
        transactionMenu();

        printf("Enter Choice: ");
        scanf("%d", &txnChoice);

        if(txnChoice == 1)
        {
            depositMoney();
        }
        else if(txnChoice == 2)
        {
            withdrawMoney();
        }
        else if(txnChoice == 3)
        {
            transferMoney();
        }
        else if(txnChoice == 4)
        {
            viewTransactions();
        }
        else if(txnChoice == 5)
        {
            searchTransactionByAccount();
        }
        else if(txnChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleLoanMenu(){
    int loanChoice;

    while(1)
    {
        loanMenu();

        printf("Enter Choice: ");
        scanf("%d", &loanChoice);

        if(loanChoice == 1)
        {
            applyLoan();
        }
        else if(loanChoice == 2)
        {
            viewLoans();
        }
        else if(loanChoice == 3)
        {
            approveLoan();
        }
        else if(loanChoice == 4)
        {
            rejectLoan();
        }
        else if(loanChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleFDMenu(){

    int fdChoice;

    while(1)
    {
        fdMenu();

        printf("Enter Choice: ");
        scanf("%d", &fdChoice);

        if(fdChoice == 1)
        {
            createFixedDeposit();
        }
        else if(fdChoice == 2)
        {
            viewFixedDeposits();
        }
        else if(fdChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleATMMenu(){

    int atmChoice;

    while(1)
    {
        atmMenu();

        printf("Enter Choice: ");
        scanf("%d", &atmChoice);

        if(atmChoice == 1)
        {
            createATMCard();
        }
        else if(atmChoice == 2)
        {
            viewATMCards();
        }
        else if(atmChoice == 3)
        {
            blockATMCard();
        }
        else if(atmChoice == 4)
        {
            unblockATMCard();
        }
        else if(atmChoice == 5)
        {
            atmLogin();
        }
        else if(atmChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleReportMenu(){int reportChoice;

    while(1)
    {
        reportMenu();

        printf("Enter Choice: ");
        scanf("%d", &reportChoice);

        if(reportChoice == 1)
        {
            accountReport();
        }
        else if(reportChoice == 2)
        {
            bankStatistics();
        }
        else if(reportChoice == 3)
        {
            top5Customers();
        }
        else if(reportChoice == 4)
        {
            generateStatement();
        }
        else if(reportChoice == 5)
        {
            monthlyRevenueReport();
        }
        else if(reportChoice == 6)
        {
            applyInterest();
        }
        else if(reportChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleSystemMenu(){

    int systemChoice;

    while(1)
    {
        systemMenu();

        printf("Enter Choice: ");
        scanf("%d", &systemChoice);

        if(systemChoice == 1)
        {
            changeAdminPassword();
        }
        else if(systemChoice == 2)
        {
            unlockAccount();
        }
        else if(systemChoice == 3)
        {
            exportCSV();
        }
        else if(systemChoice == 4)
        {
            backupDatabase();
        }
        else if(systemChoice == 5)
        {
            restoreDatabase();
        }
        else if(systemChoice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
}

void handleMainMenuChoice(int choice)
{
    switch(choice)
    {
        case 1:
            handleAccountMenu();
            break;

        case 2:
            handleTransactionMenu();
            break;

        case 3:
            handleLoanMenu();
            break;

        case 4:
            handleFDMenu();
            break;

        case 5:
            handleATMMenu();
            break;

        case 6:
            handleReportMenu();
            break;

        case 7:
            handleSystemMenu();
            break;

        default:
            printf("Invalid Choice!\n");
    }
}