#include "user.h"
#include "../Transaction data/transact.h"
#include "../Block data/block.h"

long NumberOfUsers = 0;
User* UserData = NULL;
int tablesize = 100;

long long hash(char ID[], int tablesize)
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long key = 0;
    long long index;
    long long power = 1;
    for (int i = 0; i < 10; i++)
    {
        key = (key + (ID[i] - '0' + 1) * power) % m;
    }

    return key;
}

User *SearchUserByID(char *id)
{
    User *node = (User *)malloc(sizeof(User *));
    long long key = hash(id, tablesize);
    for (int i = 0; i < tablesize; i++)
    {
        int newindex = ((key % tablesize) + i * (1 + (key % (tablesize - 1)))) % tablesize;
        if (UserData[newindex].WalletBalance != -1 && (strcmp(UserData[newindex].UniqueID, id) == 0))
            node = &UserData[newindex];
    }

    return node;
}

char *RandomID(char *ID)
{
    static char string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789123456789#?!";

    if (!srand_flag)
        __initialisesrand();

    int length = sizeof(string) - 1;
    for (int i = 0; i < 10; i++)
    {
        ID[i] = string[rand() % length];
    }

    ID[10] = '\0';
    return ID;
}

int quadprob(User *UserData, int tablesize, char ID[])
{

    long long key = hash(ID, tablesize);
    for (int i = 0; i < tablesize; i++)
    {
        int newindex = ((key % tablesize) + i * (1 + (key % (tablesize - 1)))) % tablesize;
        if (UserData[newindex].WalletBalance == -1)
        {
            return newindex;
        }
    }
}

void AddUser(int WalletBalance)
{
    time_t t;
    time(&t);

    if (UserData == NULL)
    {
        UserData = (User *)calloc(tablesize, sizeof(User));

        for (int i = 0; i < tablesize; i++)
        {
            UserData[i].WalletBalance = -1;
        }
    } //Initial size of 100 users

    else if (NumberOfUsers * 2 > tablesize)
    {
        User TempUserArray[tablesize];
        for (int i = 0; i < tablesize; i++)
        {
            TempUserArray[i] = UserData[i];
        }
        free(UserData);
        UserData = (User *)calloc(2 * tablesize, sizeof(User));
        for (int i = 0; i < 2 * tablesize; i++)
        {
            UserData[i].WalletBalance = -1;
        }
        for (int i = 0; i < tablesize; i++)
        {
            if (TempUserArray[i].WalletBalance != -1)
            {
                int position = quadprob(UserData, tablesize, TempUserArray[i].UniqueID);

                strcpy(UserData[position].UniqueID, TempUserArray[i].UniqueID);
                strcpy(UserData[position].JoinDateTime, TempUserArray[i].JoinDateTime);
                UserData[position].WalletBalance = TempUserArray[i].WalletBalance;
                UserData[position].UTH = TempUserArray[i].UTH;
            }
        }
        tablesize = tablesize * 2;
    }

    char newID[25];

    RandomID(newID);
    int position = quadprob(UserData, tablesize, newID);

    strcpy(UserData[position].UniqueID, newID);
    strcpy(UserData[position].JoinDateTime, ctime(&t));
    UserData[position].WalletBalance = WalletBalance;
    UserData[position].UTH = CreateUserTransactHistory(UserData[position].UTH);

    NumberOfUsers++;
    return position;
}