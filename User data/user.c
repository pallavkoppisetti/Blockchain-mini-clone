#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"

NumberOfUsers = 0;
UserData = NULL;

bool AddUser(long long WalletBalance)
{   
    time_t t;
    time(&t);

    if(UserData == NULL)
        UserData = (User*) calloc(100, sizeof(User));  //Initial size of 100 users;
    if(NumberOfUsers * 2 > sizeof(UserData)/sizeof(User))
        UserData = (User*)realloc(UserData, 2 * NumberOfUsers * sizeof(User));

    UserData[NumberOfUsers].ArrayID = NumberOfUsers;
    strcpy(UserData[NumberOfUsers].JoinDateTime, ctime(&t));
    UserData[NumberOfUsers].balance = WalletBalance;
    strcpy(UserData[NumberOfUsers].ID, RandomID());

    NumberOfUsers++;
}