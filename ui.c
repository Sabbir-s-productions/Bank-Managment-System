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