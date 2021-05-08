#include "transact.h"
#include "../Block data/block.h"
#include "../User data/user.h"

int NumberofTempTransactions = 0;

void InitCreateTransactHistory(pointer *Q)
{
    UserTransactionHistory *Head = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
    assert(Head != NULL);
    Head->next = NULL;
    Head->prev = NULL;
    Head->AmountTransferred = -1;
    //Head->SenderUID = NULL;

    Q->H = Head;

    UserTransactionHistory *Tail = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
    Tail->next = NULL;
    Tail->prev = NULL;
    Tail->AmountTransferred = -1;
    //Tail->SenderUID = NULL;

    Q->T = Tail;
}

pointer *CreateUserTransactHistory()
{
    pointer *Q = (pointer *)malloc(sizeof(pointer));

    InitCreateTransactHistory(Q);
    return Q;
}

void PrintUserTransactionHistory(char *UID)
{
    User *U = SearchUserByID(UID);
    UserTransactionHistory *P = U->UTH->H;
    while (P && P->next != NULL)
    {
        P = P->next;
        if (P->TranscationType == 0)
            printf("Amount received = %lld, Sender UID = %s \n", P->AmountTransferred, P->SenderUID);
        else if (P->TranscationType == 1)
            printf("Amount Sent = %lld,  Receiver UID = %s \n", P->AmountTransferred, P->ReceiverUID);
    }

    printf("\n");
}

void push(pointer *Q, long long int AmountTransferred, char *SenderUID, char *ReceiverUID, int TransactionType)
{
    if (Q->H->next == NULL) //Transaction history  IS EMPTY
    {
        UserTransactionHistory *temp = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
        temp->AmountTransferred = AmountTransferred;
        strcpy(temp->SenderUID, SenderUID);
        strcpy(temp->ReceiverUID, ReceiverUID);
        temp->TranscationType = TransactionType;
        temp->next = NULL;
        temp->prev = NULL;
        Q->H->next = temp;
        Q->T->prev = temp;
    }

    else //transaction history is not empty
    {
        UserTransactionHistory *temp = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
        temp->AmountTransferred = AmountTransferred;
        strcpy(temp->SenderUID, SenderUID);
        strcpy(temp->ReceiverUID, ReceiverUID);
        temp->TranscationType = TransactionType;
        temp->next = Q->H->next;
        temp->prev = NULL;

        Q->H->next->prev = temp;
        Q->H->next = temp;
    }
}

////////////////////////////////////////////////////////////////////////////////////////

int TransactionValidity(User *Sender, User *Receiver, long long AmountToBeTransferred)
{

    if (Sender == NULL)
    {
        return 2;
    }
    else if (Receiver == NULL)
    {
        return 3;
    }
    else if (Sender == Receiver)
    {
        return 6;
    }
    else if (Sender->WalletBalance < AmountToBeTransferred)
    {
        return 4;
    }

    else if (AmountToBeTransferred <= 0)
    {
        return 5;
    }
    return 1;
}

void UpdateUserHistory(User *Sender, User *Receiver, char *SenderUID, char *ReceiverUID, long long AmountToBeTransferred)
{
    //update user transaction history
    push(Sender->UTH, AmountToBeTransferred, SenderUID, ReceiverUID, 1);   // 1 -> amount was sent
    push(Receiver->UTH, AmountToBeTransferred, SenderUID, ReceiverUID, 0); // 0 -> amount was received

    //update user walletbalance
    Sender->WalletBalance = Sender->WalletBalance - AmountToBeTransferred;
    Receiver->WalletBalance = Receiver->WalletBalance + AmountToBeTransferred;
    printf("Transaction histories of both sender and receiver updated successfully.\n");
    return;
}

void UpdateBlockTransactionHistory(char *SenderUID, char *ReceiverUID, long long AmountToBeTransferred)
{
    if (TempTransactionArray == NULL)
    {
        TempTransactionArray = calloc(50, sizeof(BlockTransactionHistory));
    }

    strcpy(TempTransactionArray[NumberofTempTransactions].SenderUID, SenderUID);
    strcpy(TempTransactionArray[NumberofTempTransactions].ReceiverUID, ReceiverUID);
    TempTransactionArray[NumberofTempTransactions].AmountToBeTransferred = AmountToBeTransferred;

    NumberofTempTransactions++;
    if (NumberofTempTransactions == 50)
    {
        CreateBlock();
        TempTransactionArray = NULL;
        NumberofTempTransactions = 0;
    }
}

void Transact()
{
    //First search users (sender and receiver) with given IDs(T->SenderUID and T-> ReceiverUID)
    //and get pointers to the users.
    //long long SenderUID, ReceiverUID, AmountToBeTransferred;
    
    char SenderUID[40];
    char ReceiverUID[40];
    long long AmountToBeTransferred;

    printf("\nEnter the Sender UID : ");
    scanf("%s", SenderUID);
    printf("\nEnter the Receiver UID : ");
    scanf("%s", ReceiverUID);
    printf("\nEnter the amount to be transferred : ");
    scanf("%Ld", &AmountToBeTransferred);
    
    User *Sender = SearchUserByID(SenderUID);
    User *Receiver = SearchUserByID(ReceiverUID);

    int isValid = TransactionValidity(Sender, Receiver, AmountToBeTransferred);

    if (isValid == 1)
    {
        UpdateBlockTransactionHistory(SenderUID, ReceiverUID, AmountToBeTransferred);
        UpdateUserHistory(Sender, Receiver, SenderUID, ReceiverUID, AmountToBeTransferred);
        printf("Transaction successful.\n");
    }
    else if (isValid == 2)
    {
        printf("Sender does not exist in the system. Transaction aborted\n");
    }
    else if (isValid == 3)
    {
        printf("Receiver does not exist in the system. Transaction aborted\n");
    }
    else if (isValid == 4)
    {
        printf("Sender does not have enough wallet balance to complete this transaction. Transaction aborted\n");
    }
    else if (isValid == 5)
    {
        printf("Cannot transfer a non-positive value. Transaction aborted.\n");
    }
    else if (isValid == 6)
    {
        printf("Cannot transfer to self. Transaction aborted.\n");
    }
    return;
}
