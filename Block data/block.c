#include "block.h"
#include <stdlib.h>

BlockChainTail = NULL;
BlockChainHead = NULL;

long long GenerateHashValue(BlockPtr CurrentBlock) //Placeholder hash function. PS - Very bad for now
{
    return CurrentBlock->Nonce * CurrentBlock->PreviousBlockHash * CurrentBlock->Block_no;
}

int GenerateNonce(BlockPtr CurrentBlock)
{
    return (rand() % 50 + 1);
}

BlockPtr CreateNewBlock(struct Transaction TempTransactions[], BlockPtr PrevBlock)
{
    BlockPtr NewBlock = (BlockPtr)malloc(sizeof(Block)); //Might not work right now

    NewBlock->Nonce = GenerateNonce(NewBlock);

    if (BlockChainHead == NULL)
    {
        NewBlock->Block_no = 0;
        NewBlock->PreviousBlockHash = 0;
    }
    else
    {
        NewBlock->Block_no = PrevBlock->Block_no + 1;
        NewBlock->PreviousBlockHash = PrevBlock->BlockHash;
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
        PrevBlock->Next = NewBlock;
        NewBlock->Prev = PrevBlock;
    }

    NewBlock->Next = NULL;
    BlockChainTail = NewBlock;
}
