#ifndef __USER_DATA_H_
#define __USER_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

#include "../Block data/block.h"
#include "../Transaction data/transact.h"

void AddUser(int WalletBalance);
char *RandomID(char *ID);
long long hash(char ID[], int tablesize);
int quadprob(User *UserData, int tablesize, char ID[]);
User *SearchUserByID(char *ID);

extern int tablesize;

extern User *UserData;   //Array of users
extern long NumberOfUsers;   //Makes adding the user to the array easier (check if its time to double table size)

//if array reaches a certain capacity, realloc the array with double the size

#endif