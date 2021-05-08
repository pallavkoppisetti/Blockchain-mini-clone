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

User *SearchUserByID(long long int UID /*add any parameters required */);
// First search user by given ID and get pointers to the users.

int TransactionValidity(Transaction *T, User *Sender, User *Receiver);
// returns 1 if transaction is valid , 0 if transaction is invalid.

void UpdateUserHistory(Transaction *T, User *Sender, User *Receiver);
// updates user transaction history (and WalletBalance)of both sender and receiver.

pointer *CreateUserTransactHistory();
// for creating user transaction history after adding the user,it allocates memory to struct pointer containing head and tail nodes and calls InitCreateTransactHistory
// and returns pointer to struct pointer

void InitCreateTransactHistory(pointer *Q);
// this function is called in pointer *CreateUserTransactHistory() and it allocates memory 

void PrintUserTransactionHistory(UserTransactionHistory *P);
//prints user transaction history in order from latest to oldest .Parameter given is head node for now.

void push(pointer *Q, long long int AmountTransferred, long long int SenderUID, long long int ReceiverUID, int TransactionType);
// Insert item (new transaction) on the front end of the history.

Transaction *InitializeTransactionArray();
// creates an array of transactions of size 50 for storing transactions returns pointer to that array

void UpdateBlockTransactionArray(Transaction *T, Transaction *arr);
// updates the array of 50 transactions. Once the transactions are 50 passes address to the block chain .And restarts from index 0.

#endif
