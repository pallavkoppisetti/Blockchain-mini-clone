#include "../Transaction data/transact.h"
#include "block.h"

BlockPtr *BlockChainPtr = NULL;
bool srand_flag = false;
int NumberofBlocks = 0;
BlockTransactionHistory *TempTransactionArray = NULL;

void __initialisesrand()
{
    //getpid() returns the process id of the program.
    //This provides a much more randomised seed every time the program is run.
    srand(time(0) * getpid());
    srand_flag = true;
}

unsigned char *GenerateHashValue(BlockPtr cBlock)
{
    char temp2[3000] = {'\0'};
    for (int i = 0; i < 50; i++)
    {
        strcat(temp2, cBlock->TransactionList[i].ReceiverUID);
        strcat(temp2, cBlock->TransactionList[i].SenderUID);
        strcat(temp2, cBlock->TransactionList[i].TransactionTime);
    }
    unsigned char temp[4000];

    snprintf(temp, sizeof(temp), "%s %s %d %d", cBlock->PreviousBlockHash, temp2, cBlock->Nonce, cBlock->BlockNumber);

    strcpy(cBlock->BlockHash, SHA256(temp, strlen((const char *)temp), cBlock->BlockHash));

    return cBlock->BlockHash;
}

int GenerateNonce()
{
    if (!srand_flag)
        __initialisesrand();

    return (rand() % 500 + 1);
}

void CreateBlock()
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
    if (NewBlock == NULL)
    {
        printf("Memory full! No more blocks can be added to the system.\n");
        return;
    }

    NewBlock->Nonce = GenerateNonce();

    if (NumberofBlocks == 0)
    {
        NewBlock->BlockNumber = 1;
        strcpy(NewBlock->PreviousBlockHash, "0");
    }
    else
    {
        NewBlock->BlockNumber = NumberofBlocks + 1;
        strcpy(NewBlock->PreviousBlockHash, BlockChainPtr[NumberofBlocks - 1]->BlockHash);
    }

    NewBlock->TransactionList = TempTransactionArray;
    strcpy(NewBlock->BlockCreationTime, ctime(&t));
    BlockChainPtr[NumberofBlocks] = NewBlock;

    //TempTransactionArray = NULL; //Might work?

    strcpy(NewBlock->BlockHash, GenerateHashValue(NewBlock));
    NumberofBlocks++;
    printf("\nA new block has been created. Block number %d added to the blockchain.\n", NumberofBlocks);
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
        unsigned char ActualHash[70], ModifiedHash[70];
        strcpy(ActualHash, BlockChainPtr[i]->PreviousBlockHash);
        strcpy(ModifiedHash, GenerateHashValue(BlockChainPtr[i - 1]));

        //Checking if hash of previous block has been modified
        if (strcmp(ActualHash, ModifiedHash) != 0)
        {
            count++;
            printf("Attack found on block %d.\n", i);

            //Corrects Nonce until hash is corrected.
            while (strcmp(ActualHash, ModifiedHash) != 0)
            {
                BlockChainPtr[i - 1]->Nonce = (BlockChainPtr[i - 1]->Nonce % 500) + 1;
                strcpy(ModifiedHash, GenerateHashValue(BlockChainPtr[i - 1]));
            }
        }
    }

    printf("\nValidated the blockchain successfully. ");
    if (count == 0)
    {
        printf("No attacks were found.\n");
        printf("Attacks on the latest block (if any) not included in the count\n");
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
    printf("Block hash : ");

    for (int i = 0; i < strlen(BlockChainPtr[BlockNumber - 1]->BlockHash); i++)
        printf("%.2hhx", BlockChainPtr[BlockNumber - 1]->BlockHash[i]);

    printf("\n");
    printf("Previous block hash : ");

    if (strcmp(BlockChainPtr[BlockNumber - 1]->PreviousBlockHash, "0") == 0)
        printf("0");
    else
    {
        for (int i = 0; i < strlen(BlockChainPtr[BlockNumber - 1]->PreviousBlockHash); i++)
            printf("%.2hhx", BlockChainPtr[BlockNumber - 1]->PreviousBlockHash[i]);
    }
    printf("\n");
    printf("Block creation time : %s\n", BlockChainPtr[BlockNumber - 1]->BlockCreationTime);

    //Have to print transaction data also...
    int ch = 0;
    printf("Do you wish to view the transaction history of block %d? (1/0)\n", BlockNumber);
    scanf("%d", &ch);
    if (ch == 1)
    {
        printf("\nThe transaction history is as follows - \n\n");
        for (int i = 0; i < 50; i++)
        {
            printf("\nSender UID : %s\nReceiver UID : %s\nAmount : %Ld\nTransaction time : %s\n", BlockChainPtr[BlockNumber - 1]->TransactionList[i].SenderUID, BlockChainPtr[BlockNumber - 1]->TransactionList[i].ReceiverUID, BlockChainPtr[BlockNumber - 1]->TransactionList[i].AmountToBeTransferred, BlockChainPtr[BlockNumber - 1]->TransactionList[i].TransactionTime);
        }
    }
}
