#ifndef LOAN_H
#define LOAN_H

typedef struct
{
    int accountNumber;
    char name[50];
    float amount;
    int approved;
/*
0 = Pending
1 = Approved
-1 = Rejected
*/
} Loan;

void applyLoan();
void viewLoans();
void approveLoan();
void rejectLoan();

#endif