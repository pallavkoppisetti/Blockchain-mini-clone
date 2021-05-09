#include "user.h"

int main()
{
    char commands_list[][23] = {"adduser", "transact", "attack", "validateblockchain", "printusert", "printbl", "multitransact", "addmultiuser"};

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

            for (int i = 0; i < 8; i++)
            {
                printf("%s\n\n", commands_list[i]);
            }
        }

        else if (strcmp(command, "adduser") == 0)
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

        else if (strcmp(command, "multitransact") == 0)
        {
            int Number_of_users=0;
            printf("Please enter the number of transactions you would like to perform: ");
            scanf("%d",&Number_of_users);
            printf("\n");
            for(int y=0;y<Number_of_users;y++)
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

        else if (strcmp(command, "addmultiuser") == 0)
        {
            int no_of_users = 0;
            printf("Enter number of users to be added: ");
            scanf("%d", &no_of_users);
            printf("\n\n");
            for (int x = 0; x < no_of_users; x++)
            {
                long long bal2;
                printf("Enter wallet balance of user no. %d\n",x+1);
                scanf("%Ld", &bal2);
                int x = AddUser(bal2);
                if (x == -1)
                    printf("Failed to add user to the system.\n");
                else
                    printf("Your UID is : %s\n\n", UserData[x].UniqueID);
            }
        }
        else
        printf("Please type a valid command\n\n");

        printf("Continue (yes/no): ");
        scanf("%s", command);

        printf("\n");

    } while (strcmp(command, "yes") == 0);
}
