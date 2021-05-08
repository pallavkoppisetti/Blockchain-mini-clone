#ifndef __USER_DATA_H_

#define __USER_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Transaction;
//Add struct of transaction ADT

typedef struct past_transactions
{

    struct Transaction *trans;
    struct past_transactions *next;

} transactionlist;

typedef struct userinfo
{
    char ID[25];
    long ArrayID;   //stores the position of user node in the UserData array
    int balance;
    transactionlist Transaction_History;
    char JoinDateTime[50];

} User;


void AddUser(int WalletBalance);
char* RandomID(char* ID);
long long hash(char ID[], int tablesize);
int quadprob(User *UserData, int tablesize, char ID[]);
User* search(char* ID);
void initialisesrand();//for srand and to generate a seed for our randomID function

extern int tablesize=10000;

extern User* UserData=NULL;   //Array of users
extern int NumberOfUsers=0; //Makes adding the user to the array easier (check if its time to double table size)
extern bool srand_flag=false;//to ensure srand is only called once

 
//if array reaches a certain capacity, realloc the array with double the size

#endif