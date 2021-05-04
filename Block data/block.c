#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "block.h"

BlockChainTail = NULL;
BlockChainHead = NULL;
srand_flag = false;

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
    if(!srand_flag)
        __initialisesrand();

    return (rand() % 50 + 1);
}

BlockPtr CreateNewBlock(struct Transaction TempTransactions[])
{
    BlockPtr NewBlock = (BlockPtr)malloc(sizeof(Block)); //Might not work right now

    NewBlock->Nonce = GenerateNonce();

    if (BlockChainHead == NULL)
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

    //Linking the blocks;
    if (BlockChainHead == NULL)
    {
        BlockChainHead = NewBlock;
        NewBlock->Prev = NULL;
    }
    else
    {
        BlockChainTail->Next = NewBlock;
        NewBlock->Prev = BlockChainTail;
    }

    NewBlock->Next = NULL;
    BlockChainTail = NewBlock;
}

void Attack()
{   
    if(!srand_flag)
        __initialisesrand();

    int RandomBlockNumber = (rand() % 50) + 1;

    //Check if the randomly generated block number is valid
    if(RandomBlockNumber <= BlockChainTail->BlockNumber)
    {   
        //Traversing from both sides reduces the time required for searching by half
        BlockPtr LeftPtr = BlockChainHead;  
        BlockPtr RightPtr = BlockChainTail;

        //Traversing the blockchain from both sides
        while(LeftPtr && RightPtr && LeftPtr->BlockNumber <= RightPtr->BlockNumber)
        {
            if(RandomBlockNumber == LeftPtr->BlockNumber)
            {
                int Nonce = GenerateNonce();

                //To guarantee that nonce changes
                while(Nonce == LeftPtr->Nonce)
                {
                    Nonce = GenerateNonce();
                }
                LeftPtr->Nonce = Nonce;
                
                printf("Attack Successfull, Nonce of Block %d successfully modified.\n", RandomBlockNumber);
                return;
            }
            else if(RandomBlockNumber == RightPtr->BlockNumber)
            {
                int Nonce = GenerateNonce();

                //To guarantee that nonce changes
                while(Nonce == RightPtr->Nonce)
                {
                    Nonce = GenerateNonce();
                }
                LeftPtr->Nonce = Nonce;

                printf("Attack Successful, Nonce of Block %d successfully modified.\n", RandomBlockNumber);
                return;
            }
            else
            {
                LeftPtr = LeftPtr->Next;
                RightPtr = RightPtr->Prev;
            }
        }
    }

    printf("Attack Failed.\n");
    return;
}