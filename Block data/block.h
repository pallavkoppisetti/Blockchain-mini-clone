#ifndef __BLOCK_H_
#define __BLOCK_H_

typedef struct Block Block;
typedef Block *BlockPtr;

struct Block
{
    int BlockNumber;
    int Nonce;
    long long BlockHash;
    long long PreviousBlockHash;
    struct Transaction *TransactionList; //Placeholder for array of transactions
    BlockPtr Next;
    BlockPtr Prev;
};

extern BlockPtr BlockChainHead; //Keeps track of the head of the blockchain
extern BlockPtr BlockChainTail; //Keeps track of the last block in the blockchain
extern bool srand_flag;

void __initialisesrand();
//To ensure that srand is called only once, otherwise rand() won't work properly sometimes

long long GenerateHashValue(BlockPtr CurrentBlock);
//Generates hash for the current block by using
//the information stored in the current block

BlockPtr CreateNewBlock(struct Transaction TempTransactions[]);
//Creates a new block and adds it to the blockchain. Adds the transaction information
//(assuming it to be stored as a struct array temporarily)

int GenerateNonce();
//Generates a random nonce value for the currently selected block;

void Attack();
//Generate random block number from 1 to 50,
//If such a block exists, modify its nonce

//IMP - Might need doubly linked list to account for validating the blockchain

#endif