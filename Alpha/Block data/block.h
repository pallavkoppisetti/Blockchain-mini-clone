#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../Transaction data/transact.h"
#include "../User data/user.h"

typedef struct Block Block;
typedef struct BlockTransactionHistory BlockTransactionHistory;
typedef Block *BlockPtr;

struct Block
{   
    char BlockCreationTime[40];
    int BlockNumber;
    int Nonce;
    long long BlockHash;
    long long PreviousBlockHash;
    struct BlockTransactionHistory *TransactionList; //Placeholder for array of transactions   
};

struct BlockTransactionHistory
{
    char SenderUID[20];
    char ReceiverUID[20];
    long long AmountToBeTransferred;
    char TransactionTime[40];
};

extern BlockPtr* BlockChainPtr;  //Array of Block pointers. ith pointer points to block with block number i + 1;
extern bool srand_flag;
extern int NumberofBlocks; //Keeps track of the number of blocks in the blockchain
extern BlockTransactionHistory* TempTransactionArray;

void __initialisesrand();
//To ensure that srand is called only once, otherwise rand() won't work properly sometimes

unsigned long long GenerateHashValue(BlockPtr CurrentBlock);
//Generates hash for the current block by using
//the information stored in the current block

void CreateBlock();
//Creates a new block and adds it to the blockchain. Adds the transaction information
//(assuming it to be stored as a struct array temporarily)

int GenerateNonce();
//Generates a random nonce value for the currently selected block;

void Attack();
//Generate random block number from 1 to 50,
//If such a block exists, modify its nonce

void ValidateBlockChain();
//Checks if blockchain is valid
//Else modify nonce of corrupt block to match BlockHash with PreviousBlockHash of next block

void PrintBlock(int BlockNumber);
//Prints the details of the given block

#endif