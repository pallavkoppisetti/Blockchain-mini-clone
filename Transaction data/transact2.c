#include "transact2.h"

void InitCreateTransactHistory(pointer *Q)
{
    UserTransactionHistory *Head = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
    assert(Head != NULL);
    Head->next = NULL;
    Head->prev = NULL;
    Head->AmountTransferred = 0;
    Head->SenderUID = 0;

    Q->H = Head;

    UserTransactionHistory *Tail = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
    Tail->next = NULL;
    Tail->prev = NULL;
    Tail->AmountTransferred = 0;
    Tail->SenderUID = 0;

    Q->T = Tail;
}

pointer *CreateUserTransactHistory()
{
    pointer *Q = (pointer *)malloc(sizeof(pointer));

    InitCreateTransactHistory(Q);
    return Q;
}

void PrintUserTransactionHistory(UserTransactionHistory *P)
{
    while (P->next != NULL)
    {
        P = P->next;
        printf("Amount received = %lld  Sender UID = %lld \n", P->AmountTransferred, P->SenderUID);
    }

    printf("\n");
}

void push(pointer *Q, ElementType AmountTransferred, ElementType SenderUID)
{
    if (Q->H->next == NULL) //Transaction history  IS EMPTY
    {
        UserTransactionHistory *temp = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
        temp->AmountTransferred = AmountTransferred;
        temp->SenderUID = SenderUID;
        temp->next = NULL;
        temp->prev = NULL;
        Q->H->next = temp;
        Q->T->prev = temp;
    }

    else //transaction history is not empty
    {
        UserTransactionHistory *temp = (UserTransactionHistory *)malloc(sizeof(UserTransactionHistory));
        temp->AmountTransferred = AmountTransferred;
        temp->SenderUID = SenderUID;
        temp->next = Q->H->next;
        temp->prev = NULL;

        Q->H->next->prev = temp;
        Q->H->next = temp;
    }
}

////////////////////////////////////////////////////////////////////////////////////////

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
    //update user transaction history
    push(Sender->UTH, -(T->AmountToBeTransferred), T->ReceiverUID);
    push(Receiver->UTH, T->AmountToBeTransferred, T->SenderUID);

    //update user walletbalance
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

Transaction* InitializeTransactionArray()
{
Transaction* arr=(Transaction*)malloc(50*sizeof(Transaction));
assert(arr!=NULL);
ind =0;
return arr;
}

void UpdateBlockTransactionArray(Transaction* T,Transaction* arr)
{  
    if(ind>49)//when the array is full
    {    
   
    Transaction* ptraddress = arr;
    // To Do - assign it(ptraddress) to block's transaction part
    ptraddress=NULL;
    ind=0;
    arr=(Transaction*)malloc(50*sizeof(Transaction));
    assert(arr!=NULL);
    }
    
    if(0<=ind && ind<=49)
    {    
 
    arr[ind].AmountToBeTransferred=T->AmountToBeTransferred;
    arr[ind].ReceiverUID=T->ReceiverUID;
    arr[ind].SenderUID=T->SenderUID;
    ind++;
    }

}
