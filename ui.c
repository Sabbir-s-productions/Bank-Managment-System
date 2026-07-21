#include <stdio.h>
#include <windows.h>
#include "ui.h"

void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}

void line()
{
    printf("=========================================\n");
}

void title()
{
    setColor(11);

    line();
    printf("      BANK MANAGEMENT SYSTEM V3.0\n");
    line();

    setColor(7);
}

void accountCard()
{
    setColor(11);

    printf("\n");
    printf("=========================================\n");
    printf("             ACCOUNT CARD\n");
    printf("=========================================\n");

    setColor(7);
}

void showMainMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("      BANK MANAGEMENT SYSTEM v2.0\n");
    printf("========================================\n");

    printf("1. Account Management\n");
    printf("2. Transaction Management\n");
    printf("3. Loan Management\n");
    printf("4. Fixed Deposit Management\n");
    printf("5. ATM Services\n");
    printf("6. Reports & Analytics\n");
    printf("7. System Tools\n");
    printf("0. Exit\n");

    printf("========================================\n");
}

void accountMenu()
{
    printf("\n===== ACCOUNT MANAGEMENT =====\n");

    printf("1. Create Account\n");
    printf("2. View Accounts\n");
    printf("3. Search Account\n");
    printf("4. Edit Account\n");
    printf("5. Delete Account\n");
    printf("6. Check Balance\n");
    printf("7. Search By Name\n");
    printf("8. Change PIN\n");
    printf("0. Back\n");
}

void transactionMenu()
{
    printf("\n===== TRANSACTION MANAGEMENT =====\n");

    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. View Transaction History\n");
    printf("5. Search Transactions By Account\n");
    printf("0. Back\n");
}

void loanMenu()
{
    printf("\n===== LOAN MANAGEMENT =====\n");

    printf("1. Apply For Loan\n");
    printf("2. View Loan Requests\n");
    printf("3. Approve Loan\n");
    printf("4. Reject Loan\n");
    printf("0. Back\n");
}

void fdMenu()
{
    printf("\n===== FIXED DEPOSIT MANAGEMENT =====\n");

    printf("1. Create Fixed Deposit\n");
    printf("2. View Fixed Deposits\n");
    printf("0. Back\n");
}

void atmMenu()
{
    printf("\n===== ATM SERVICES =====\n");

    printf("1. Create ATM Card\n");
    printf("2. View ATM Cards\n");
    printf("3. Block ATM Card\n");
    printf("4. Unblock ATM Card\n");
    printf("5. ATM Login\n");
    printf("0. Back\n");
}

void reportMenu()
{
    printf("\n===== REPORTS & ANALYTICS =====\n");

    printf("1. Account Report\n");
    printf("2. Bank Statistics\n");
    printf("3. Top 5 Richest Customers\n");
    printf("4. Generate Account Statement\n");
    printf("5. Monthly Revenue Report\n");
    printf("6. Apply Interest\n");
    printf("0. Back\n");
}

void systemMenu()
{
    printf("\n===== SYSTEM TOOLS =====\n");

    printf("1. Change Admin Password\n");
    printf("2. Unlock Account\n");
    printf("3. Export CSV\n");
    printf("4. Backup Database\n");
    printf("5. Restore Database\n");
    printf("0. Back\n");
}

void mainMenu()
{
    printf("1. Show Account Menu\n");
    printf("2. Show Transaction Menu\n");
    printf("3. Show Loan Menu\n");
    printf("4. Show Fixed Deposit Menu\n");
    printf("5. Show ATM Menu\n");
    printf("6. Show Report Menu\n");
    printf("7. Show System Menu\n");
    printf("0. Exit\n");
}

void loginMenu()
{
    printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
    printf("1. Admin Login\n");
    printf("2. Customer Login\n");
    printf("3. Exit\n");
}

void goodbyeMessage()
{
    printf("\n=================================\n");
    printf("Thank You For Using Bank Management System\n");
    printf("=================================\n");
}