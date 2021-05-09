#include "block.h"
#include "../Transaction data/transact2.h"

BlockChainPtr = NULL;
srand_flag = false;
NumberofBlocks = 0;

void __initialisesrand()
{
    //getpid() returns the process id of the program.
    //This provides a much more randomised seed every time the program is run.
    srand(time(0) * getpid());
    srand_flag = true;
}

long long int convert_transactarr_integer(Transaction* T)
{
    
  long long int NUM = 0;
  long long int arr[50];
  
  for(int i = 0;i < 50;i++){

      arr[i] = (T[i]->senderUID % 55) + T[i]->ReceiverUID[i] + (T[i]->AmountToBeTransferred % 10000);
      NUM = NUM + arr[i];
      
  }

  return NUM;

}

void GenerateHashValue(unsigned char *Blockhash, int BlockNumber, Transaction *transactions, char *PreviousBlockHash, int Nonce)
{
   unsigned char temp[10000];
   long long int transaction_NUM = convert_transactarr_integer(transactions);
    
   snprintf(temp, sizeof(temp), "%d,%s,%d,%lld", BlockNumber,PreviousBlockHash,Nonce, transaction_NUM);
   SHA1(temp, strlen((const char *)temp), Blockhash);
    
   return;
    
}

int GenerateNonce()
{
    if (!srand_flag)
        __initialisesrand();

    return (rand() % 500 + 1);
}

BlockPtr CreateNewBlock(struct Transaction TempTransactions[])
{
    time_t t;
    time(&t);

    if (BlockChainPtr == NULL)
    {
        //Initial size of 50 blocks.
        BlockChainPtr = (BlockPtr *)calloc(50, sizeof(BlockPtr));
    }
    else if (NumberofBlocks * 2 > sizeof(BlockChainPtr) / sizeof(BlockPtr))
    {
        BlockChainPtr = realloc(BlockChainPtr, NumberofBlocks * 2 * sizeof(BlockPtr));
    }

    BlockPtr NewBlock = (BlockPtr)malloc(sizeof(Block)); //Might not work right now
    if(NewBlock == NULL)
    {
        printf("Memory full! No more blocks can be added to the system.\n");
        return;
    }

    NewBlock->Nonce = GenerateNonce();

    if (NumberofBlocks == 0)
    {
        NewBlock->BlockNumber = 1;
        NewBlock->PreviousBlockHash = 0;
    }
    else
    {
        NewBlock->BlockNumber = NumberofBlocks + 1;
        NewBlock->PreviousBlockHash = BlockChainPtr[NumberofBlocks - 1]->BlockHash;
    }

    NewBlock->TransactionList = TempTransactions;
    strcpy(NewBlock->BlockCreationTime, ctime(&t));

    TempTransactions = NULL; //Might work?

    NewBlock->BlockHash = GenerateHashValue(NewBlock);

    BlockChainPtr[NumberofBlocks] = NewBlock;
    NumberofBlocks++;
}

void Attack()
{
    if (!srand_flag)
        __initialisesrand();

    int RandomBlockNumber = (rand() % 50) + 1;

    //Searching is O(1).
    //Check if the randomly generated block number is valid
    if (RandomBlockNumber <= NumberofBlocks)
    {
        int Nonce = GenerateNonce();

        //To ensure that Nonce is always modified
        while (Nonce == BlockChainPtr[RandomBlockNumber - 1]->Nonce)
        {
            Nonce = GenerateNonce();
        }
        BlockChainPtr[RandomBlockNumber - 1]->Nonce = Nonce;

        printf("Attack successful, nonce of block %d modified successfully.\n", RandomBlockNumber);
        return;
    }

    printf("Attack Failed.\n");
    return;
}

void ValidateBlockChain()
{
    int count = 0;

    for (int i = NumberofBlocks - 1; i >= 1; i--)
    {
        long long ActualHash = BlockChainPtr[i]->PreviousBlockHash;
        long long ModifiedHash = GenerateHashValue(BlockChainPtr[i - 1]);

        //Checking if hash of previous block has been modified
        if (ActualHash != ModifiedHash)
        {
            count++;
            printf("Attack found on block %d.\n", i);

            //Corrects Nonce until hash is corrected.
            while (ActualHash != ModifiedHash)
            {
                BlockChainPtr[i - 1]->Nonce = (BlockChainPtr[i - 1]->Nonce % 500) + 1;
                ModifiedHash = GenerateHashValue(BlockChainPtr[i - 1]);
            }
        }
    }

    printf("Validated the blockchain successfully. ");
    if (count == 0)
    {
        printf("No attacks were found.\n");
    }
    else
    {   
        printf("%d unique attack(s) was(were) found, all of the affected blocks were corrected.\n", count);
        printf("Attacks on the latest block (if any) not included in the count\n");
    }

    return;
}

void PrintBlock(int BlockNumber)
{
    //Check if the block number is valid
    if (BlockNumber > NumberofBlocks)
    {
        printf("Invalid block number.\n");
        return;
    }

    printf("Block number : %d\n", BlockNumber);
    printf("Block nonce : %d\n", BlockChainPtr[BlockNumber - 1]->Nonce);
    printf("Block hash : %016Lx\n", BlockChainPtr[BlockNumber - 1]->BlockHash);
    printf("Previous block hash : %016Lx\n", BlockChainPtr[BlockNumber - 1]->PreviousBlockHash);
    printf("Block creation time : %s\n", BlockChainPtr[BlockNumber - 1]->BlockCreationTime);

    //Have to print transaction data also...
}
