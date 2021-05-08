#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"

void initialisesrand()
{
    //getpid() returns the process id of the program.
    //This provides a much more randomised seed every time the program is run.
    srand(time(0) * getpid());
    srand_flag = true;
}

char *RandomID(char *ID)
{
    static char string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789123456789#?!";

    if (!srand_flag)
        initialisesrand();

    int length = sizeof(string) - 1;
    for (int i = 0; i < 10; i++)
    {
        ID[i] = string[rand() % length];
    }

    ID[10] = '\0';
    return ID;
}

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

int quadprob(User *UserData, int tablesize, char ID[])
{

    long long key = hash(ID, tablesize);
    for (int i = 0; i < tablesize; i++)
    {
        int newindex = ((key % tablesize) + i * (1 + (key % (tablesize - 1)))) % tablesize;
        if (UserData[newindex].balance == 0)
        {
            return newindex;
        }
    }
}

User *search(char *id)
{
    User *node = (User *)malloc(sizeof(User *));
    long long key = hash(id, tablesize);
    for (int i = 0; i < tablesize; i++)
    {
        int newindex = ((key % tablesize) + i * (1 + (key % (tablesize - 1)))) % tablesize;
        if (UserData[newindex].balance != 0 && (strcmp(UserData[newindex].ID, id) == 0))
            node = &UserData[newindex];
    }

    return node;
}

void AddUser(int WalletBalance)
{
    time_t t;
    time(&t);

    if (UserData == NULL)
    {
        UserData = (User *)malloc(tablesize * sizeof(User));

        for (int i = 0; i < 10000; i++)
        {
            UserData[i].balance = 0;
        }
    } //Initial size of 10000 users

    if (NumberOfUsers * 2 > sizeof(UserData) / sizeof(User))
    {
        tablesize = tablesize * 2;
        UserData = (User *)realloc(UserData, tablesize * sizeof(User));
    }

    char newID[25];

    RandomID(newID);
    int position = quadprob(UserData, tablesize, newID);

    strcpy(UserData[position].ID, newID);
    strcpy(UserData[position].JoinDateTime, ctime(&t));
    UserData[position].balance = WalletBalance;

    NumberOfUsers++;
}

