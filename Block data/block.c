#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "block.h"

BlockChainTail = NULL;
BlockChainPtr = NULL;
srand_flag = false;
NumberofBlocks = 0;

void __initialisesrand()
{
    srand(time(0) * getpid());
    srand_flag = true;
}

long long GenerateHashValue(BlockPtr CurrentBlock) //Placeholder hash function. PS - Very bad for now
{
    return CurrentBlock->Nonce * CurrentBlock->PreviousBlockHash * CurrentBlock->BlockNumber;
}

int GenerateNonce()
{
    if (!srand_flag)
        __initialisesrand();

    return (rand() % 500 + 1);
}

void initialiseBlockChain()
{
    if (BlockChainPtr == NULL)
    {
        //Assuming atmost 10000 blocks can be present
        BlockChainPtr = (BlockPtr *)calloc(10000, sizeof(BlockPtr));
    }
}

BlockPtr CreateNewBlock(struct Transaction TempTransactions[])
{
    BlockPtr NewBlock = (BlockPtr)malloc(sizeof(Block)); //Might not work right now

    NewBlock->Nonce = GenerateNonce();

    if (NumberofBlocks == 0)
    {
        NewBlock->BlockNumber = 1;
        NewBlock->PreviousBlockHash = 0;
    }
    else
    {
        NewBlock->BlockNumber = BlockChainTail->BlockNumber + 1;
        NewBlock->PreviousBlockHash = BlockChainTail->BlockHash;
    }

    NewBlock->TransactionList = TempTransactions;

    TempTransactions = NULL; //Might work?

    NewBlock->BlockHash = GenerateHashValue(NewBlock);

    //Current design only allows the first block with a given hash.
    //A second block with same hash won't be added to the blockchain
    if (BlockChainPtr[NewBlock->BlockHash] == NULL)
    {
        BlockChainPtr[NewBlock->BlockHash] = NewBlock;
        NumberofBlocks++;
    }

    BlockChainTail = NewBlock;
}

void Attack()
{
    if (!srand_flag)
        __initialisesrand();

    int RandomBlockNumber = (rand() % 50) + 1;

    //Check if the randomly generated block number is valid
    if (RandomBlockNumber <= NumberofBlocks)
    {
        //Since the block numbers are not in a sequential order, binary search is not viable.
        //Searching from both ends reduces time requires by half
        int Left = 0;
        int Right = 9999;

        while (Left <= Right)
        {
            if (BlockChainPtr[Left]->BlockNumber == RandomBlockNumber)
            {
                int Nonce = GenerateNonce();

                //To ensure that Nonce is always modified
                while (Nonce == BlockChainPtr[Left]->Nonce)
                {
                    Nonce = GenerateNonce();
                }
                BlockChainPtr[Left]->Nonce = Nonce;

                printf("Attack successful, Nonce of Block %d modified successfully.\n", RandomBlockNumber);
                return;
            }
            else if (BlockChainPtr[Right]->BlockNumber == RandomBlockNumber)
            {
                int Nonce = GenerateNonce();

                //To ensure that Nonce is always modified
                while (Nonce == BlockChainPtr[Right]->Nonce)
                {
                    Nonce = GenerateNonce();
                }
                BlockChainPtr[Right]->Nonce = Nonce;

                printf("Attack successful, Nonce of Block %d modified successfully.\n", RandomBlockNumber);
                return;
            }

            Left++;
            Right--;
        }
    }

    printf("Attack Failed.\n");
    return;
}

void ValidateBlockChain()
{
    long long CurrentHash = BlockChainTail->BlockHash;

    for (int i = 0; i < NumberofBlocks; i++)
    {
        long long PreviousBlockHash = BlockChainPtr[CurrentHash]->PreviousBlockHash;
        long long ModifiedHash = GenerateHashValue(BlockChainPtr[PreviousBlockHash]);

        //Checking if hash of previous block has been modified
        while (PreviousBlockHash != ModifiedHash)
        {
            BlockChainPtr[PreviousBlockHash]->Nonce = (BlockChainPtr[PreviousBlockHash]->Nonce % 500) + 1;
            ModifiedHash = GenerateHashValue(BlockChainPtr[PreviousBlockHash]);
        }

        CurrentHash = PreviousBlockHash;
    }
}
