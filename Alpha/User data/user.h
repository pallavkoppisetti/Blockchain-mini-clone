#ifndef __USER_DATA_H_
#define __USER_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "../Transaction data/transact.h"
#include "../Block data/block.h"

void AddUser(long long int WalletBalance);

extern User* UserArray;   //Array of users
extern long NumberOfUsers; //Makes adding the user to the array easier (constant time)

//Check if this is a good idea : We store the users in a linked 
//if array reaches a certain capacity, realloc the array with double the size

#endif