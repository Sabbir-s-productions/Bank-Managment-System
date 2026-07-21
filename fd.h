#ifndef FD_H
#define FD_H

typedef struct
{
    int fdID;
    float amount;
    float rate;
    int years;
    float maturity;
} FixedDeposit;

void createFixedDeposit();
void viewFixedDeposits();

#endif