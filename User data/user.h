#ifndef __USER_DATA_H_

#define __USER_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Transaction;
//Add struct of transaction ADT

typedef struct past_transactions
{

    struct Transaction *trans;
    struct past_transactions *next;

} transactionlist;

typedef struct userinfo
{
    char ID[25];
    long ArrayID;   //stores the position of user node in the UserData array
    long long int balance;
    transactionlist Transaction_History;
    char JoinDateTime[50];

} User;

bool AddUser(long long int WalletBalance);
char RandomID();

extern User* UserData;   //Array of users
extern long NumberOfUsers; //Makes adding the user to the array easier (constant time)

//Check if this is a good idea : We store the users in a linked 
//if array reaches a certain capacity, realloc the array with double the size

#endif