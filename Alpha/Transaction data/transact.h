#ifndef __TRANSACT_H_
#define __TRANSACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <openssl/sha.h>

typedef struct User User;
typedef struct UserTransactionHistory UserTransactionHistory;
typedef struct pointer pointer;

struct User
{
    char UniqueID[20];
    long long WalletBalance;
    pointer *UTH;
    char JoinDateTime[40];
};

struct UserTransactionHistory
{
    long long AmountTransferred;
    char SenderUID[20];
    char ReceiverUID[20];
    char TransactionTime[40];
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

int TransactionValidity(User *Sender, User *Receiver, long long AmountToBeTransferred);
//returns 1 if transaction is valid , 0 if transaction is invalid.

void UpdateUserHistory(User *Sender, User *Receiver, char *SenderUID, char *ReceiverUID, long long AmountToBeTransferred);
// updates user transaction history (and WalletBalance)of both sender and receiver.

pointer *CreateUserTransactHistory();

void InitCreateTransactHistory(pointer *Q);

void PrintUserTransactionHistory(char *UID);

void PrintUserDetails(char *UID);

void push(pointer *Q, long long AmountTransferred, char *SenderUID, char *ReceiverUID, int TransactionType);
//Insert item on the front end of the list.

void UpdateBlockTransactionHistory();

void Transact();

#endif
