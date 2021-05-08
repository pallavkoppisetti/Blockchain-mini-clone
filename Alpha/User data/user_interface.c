#include "user.h"

int main()
{
    char commands_list[][23] = {"adduser", "transact", "attack", "validateblockchain", "printusert", "printbl"};

    char command[23];

    do
    {
        printf("->Pls type the command \n");
        printf(" (Type in \"list\" to know what tasks you can perform)\n\n");

        scanf("%s", command);
        printf("\n");

        if (strcmp(command, "list") == 0)
        {

            //lists all the functions that can be performed

            for (int i = 0; i < 4; i++)
            {
                printf("%s\n\n", commands_list[i]);
            }
        }

        if (strcmp(command, "adduser") == 0)
        {
            long long bal;
            printf("Enter wallet balance\n");
            scanf("%Ld", &bal);
            int x = AddUser(bal);
            if (x == -1)
                printf("Failed to add user to the system.\n");
            else
                printf("Your UID is : %s\n", UserData[x].UniqueID);
        }

        else if (strcmp(command, "attack") == 0)
        {
            Attack();
        }
        else if (strcmp(command, "printbl") == 0)
        {
            int num;
            printf("Enter block number : \n");
            scanf("%d", &num);
            PrintBlock(num);
        }
        else if (strcmp(command, "transact") == 0)
        {
            Transact();
        }
        else if (strcmp(command, "validateblockchain") == 0)
        {
            ValidateBlockChain();
        }
        else if (strcmp(command, "printusert") == 0)
        {
            char UID[40];
            printf("Enter UID : \n");
            scanf("%s", UID);
            PrintUserTransactionHistory(UID);
        }
        printf("Continue (yes/no): ");
        scanf("%s", command);

        printf("\n");

    } while (strcmp(command, "yes") == 0);
}
