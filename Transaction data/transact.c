#include "transact.h"

User *SearchUserByID(long long int UID /*,pointer to array of pointers to users*/)
{
}

int TransactionValidity(Transaction *T, User *Sender, User *Receiver)
{

    if (Sender == NULL || Receiver == NULL)
    {
        return 0;
    }

    if (Sender->WalletBalance < T->AmountToBeTransferred)
    {
        return 0;
    }
    if (T->AmountToBeTransferred <= 0)
    {
        return 0;
    }   

    return 1;
}

void UpdateUserHistory(Transaction *T, User *Sender, User *Receiver)
{
    //update user transaction history ->not done yet
    //if we use arrays for storing transaction history of each user then update 
    // element with index = no of transactions 
    // and update no of transactions++;
    // Doubling the size of array if array is already full.


    Sender->WalletBalance = Sender->WalletBalance - T->AmountToBeTransferred;
    Receiver->WalletBalance = Receiver->WalletBalance + T->AmountToBeTransferred;
    return;
}

void Transact(Transaction *T)
{
    //First search users (sender and receiver) with given IDs(T->SenderUID and T-> ReceiverUID)
    //and get pointers to the users.
    User *Sender = User * SearchUserByID(T->SenderUID);
    User *Receiver = User * SearchUserByID(T->ReceiverUID);

    int valid = TransactionValidity(T, Sender, Receiver);

    if (valid == 0)
    {
        printf("Transaction invalid\n");
    }

    else //if(valid==1)
    {
        UpdateUserHistory(T, Sender, Receiver);
        printf("Transaction done successfully\n");
    }

    return;
}
