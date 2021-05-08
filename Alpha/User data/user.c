#include "user.h"
#include "../Transaction data/transact.h"
#include "../Block data/block.h"

long NumberOfUsers = 0;
User* UserArray = NULL;

void AddUser(long long WalletBalance)   //placeholder add user function
{
    time_t t;
    time(&t);

    if (UserArray == NULL)
        UserArray = (User *)calloc(100, sizeof(User)); //Initial size of 100 users;
    if (NumberOfUsers * 2 > sizeof(UserArray) / sizeof(User))
        UserArray = (User *)realloc(UserArray, 2 * NumberOfUsers * sizeof(User));

    UserArray[NumberOfUsers].UniqueID = NumberOfUsers;
    strcpy(UserArray[NumberOfUsers].JoinDateTime, ctime(&t));
    UserArray[NumberOfUsers].WalletBalance = WalletBalance;
    //strcpy(UserArray[NumberOfUsers]->ID, RandomID());
    UserArray[NumberOfUsers].UTH = CreateUserTransactHistory(UserArray[NumberOfUsers].UTH);

    NumberOfUsers++;
}