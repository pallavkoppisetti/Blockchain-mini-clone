#ifndef __TRANSACT_H_
#define __TRANSACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

typedef struct User User;
typedef struct UserTransactionHistory UserTransactionHistory;
typedef struct pointer pointer;

struct User
{
    long long int UniqueID;
    long long int WalletBalance;
    pointer *UTH;
    char JoinDateTime[50];
};

struct UserTransactionHistory
{
    long long int AmountTransferred;
    long long int SenderUID;
    long long int ReceiverUID;
    int TranscationType; // 0 -> Amount Received, 1 -> Amount Sent
    UserTransactionHistory *next;
    UserTransactionHistory *prev;
};

struct pointer
{
    UserTransactionHistory *H;
    UserTransactionHistory *T;
};

extern int NumberofTempTransactions;

User *SearchUserByID(long long int UID /*,pointer to array of pointers to users*/);
//First search user by given ID and get pointers to the users.

int TransactionValidity(User *Sender, User *Receiver, long long AmountToBeTransferred);
//returns 1 if transaction is valid , 0 if transaction is invalid.

void UpdateUserHistory(User *Sender, User *Receiver, long long SenderUID, long long ReceiverUID, long long AmountToBeTransferred);
// updates user transaction history (and WalletBalance)of both sender and receiver.

pointer *CreateUserTransactHistory();

void InitCreateTransactHistory(pointer *Q);

void PrintUserTransactionHistory(long long UID);

void push(pointer *Q, long long int AmountTransferred, long long int SenderUID, long long int ReceiverUID, int TransactionType);
//Insert item on the front end of the list.

void UpdateBlockTransactionHistory();

void Transact();

#endif
