#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct
{
    int accountNumber;
    char name[100];
    int pin;
    float balance;
    char accountType[20];
    int isActive;
} Account;

int isDuplicateAccount(int accNo);

void createAccount();
void viewAccounts();
void searchAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void deleteAccount();
void changePIN();
void searchByName();
void accountReport();
void generateStatement();

#endif