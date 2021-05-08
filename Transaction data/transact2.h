#ifndef TRANSACT_H
#define TRANSACT_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

int ind;

typedef struct Transaction Transaction;
typedef struct User User;
typedef struct UserTransactionHistory UserTransactionHistory;
typedef long long int ElementType;
typedef struct pointer pointer;


struct Transaction
{
    long long int SenderUID;
    long long int ReceiverUID;
    long long int AmountToBeTransferred;
    
};

struct User
{
    long long int UniqueID;
    long long int WalletBalance;
    pointer *UTH;
    char *JoinDateTime;
};

struct UserTransactionHistory
{
    long long int AmountTransferred;
    long long int SenderUID;
    UserTransactionHistory* next;
    UserTransactionHistory* prev;
};

struct pointer
{
UserTransactionHistory* H;
UserTransactionHistory* T;
};


User *SearchUserByID(long long int UID /*,pointer to array of pointers to users*/);
//First search user by given ID and get pointers to the users.

int TransactionValidity(Transaction *T, User *Sender, User *Receiver);
//returns 1 if transaction is valid , 0 if transaction is invalid.

void UpdateUserHistory(Transaction *T, User *Sender, User *Receiver);
// updates user transaction history (and WalletBalance)of both sender and receiver.

pointer* CreateUserTransactHistory();

void InitCreateTransactHistory(pointer* Q);

void PrintUserTransactionHistory(UserTransactionHistory* P);

void push(pointer* Q,ElementType AmountTransferred,ElementType SenderUID);
//Insert item on the front end of the list.

#endif
