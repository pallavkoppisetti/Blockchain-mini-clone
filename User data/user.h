#ifndef __USER_DATA_

#define __USER_DATA_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include<stdbool.h>

typedef struct Transaction;

typedef struct past_transactions
{

    struct Transaction *trans;
    struct past_transactions *next;

} transactionlist;

typedef struct userinfo
{
    char ID[25];
    long long int balance;
    transactionlist Transaction_History;
    char JoinDateTime[11];

}node;

bool AddUser(long long int WalletBalance,char JoinDate[]);
char RandomID();


#endif