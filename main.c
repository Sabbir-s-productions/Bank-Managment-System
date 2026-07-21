#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


#include "admin.h"



#include "menu.h"
#include "customer.h"



int main()
{
    createDefaultPassword();

int role;

loginMenu();
printf("Enter Choice: ");
scanf("%d", &role);

if(role == 1)
{
    login();
    dashboard();
}
else if(role == 2)
{
    customerLogin();
    return 0;
}
else
{
    return 0;
}

    int choice;

    while(1)
    {
        title();

  
        mainMenu();
        
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 0)
{
    goodbyeMessage();
    break;
}

handleMainMenuChoice(choice);
    }
    return 0;
}