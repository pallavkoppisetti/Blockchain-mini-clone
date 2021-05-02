#ifndef TRANSACT_H
#define TRANSACT_H

#include "user.h"

typedef struct Transaction Transaction;


struct Transaction
{
    long long int SenderUID;
    long long int ReceiverUID;
    long long int AmountToBeTransferred;
};


User *SearchUserByID(long long int UID /*,pointer to array of pointers to users*/);
//First search user by given ID and get pointers to the users.

int TransactionValidity(Transaction *T, User *Sender, User *Receiver);
//returns 1 if transaction is valid , 0 if transaction is invalid.

void UpdateUserHistory(Transaction *T, User *Sender, User *Receiver);
// updates user transaction history (and WalletBalance)of both sender and receiver.

#endif
