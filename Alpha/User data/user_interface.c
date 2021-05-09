#include "user.h"

int main()
{
    char commands_list[][23] = {"adduser", "transact", "attack", "validateblockchain", "userdetails", "blockdetails", "multitransact", "addmultiuser", "exit"};

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

            for (int i = 0; i < 9; i++)
            {
                printf("%s\n\n", commands_list[i]);
            }
        }

        else if (strcmp(command, "adduser") == 0)
        {
            //this command adds a user and assigns a randomly generated ID(alphanumeric string)
            int x = AddUser();
            printf("Your User ID is : %s\n", UserData[x].UniqueID);
        }

        else if (strcmp(command, "attack") == 0)
        {
            //generates a number between 1 to 50.checks if such a blocknumber exists, if so, update nonce of that block
            Attack();
        }
        else if (strcmp(command, "blockdetails") == 0)
        {
            //prints details of a block

            int num;
            printf("Enter block number : \n");
            scanf("%d", &num);
            PrintBlock(num);
        }

        else if (strcmp(command, "transact") == 0)
        {
            //initiates a transaction
            Transact();
        }

        else if (strcmp(command, "multitransact") == 0)
        {
            //perform multiple transactions

            int Number_of_users = 0;
            printf("Please enter the number of transactions you would like to perform: ");
            scanf("%d", &Number_of_users);
            printf("\n");
            for (int y = 0; y < Number_of_users; y++)
                Transact();
        }

        else if (strcmp(command, "validateblockchain") == 0)
        {
            //verifies Previousblockhash and checks for attacks
            ValidateBlockChain();
        }

        else if (strcmp(command, "userdetails") == 0)
        {
            //prints the user details
            char UID[20];
            printf("Enter User ID : \n");
            scanf("%s", UID);
            PrintUserDetails(UID);
        }

        else if (strcmp(command, "addmultiuser") == 0)
        {
            //used to add multiple users

            int no_of_users = 0;
            printf("Enter number of users to be added: ");
            scanf("%d", &no_of_users);
            printf("\n\n");
            for (int x = 0; x < no_of_users; x++)
            {
                long double bal2;
                printf("Enter wallet balance of user no. %d\n", x + 1);
                scanf("%Lg", &bal2);
                int x = AddUser(bal2);
                if (x == -1)
                    printf("Failed to add user to the system.\n");
                else
                    printf("Your UID is : %s\n\n", UserData[x].UniqueID);
            }
        }
        else if (strcmp(command, "exit") == 0)
            exit(0);
        else
            printf("Please type a valid command\n\n");

        printf("Continue (yes/no): ");
        scanf("%s", command);

        printf("\n");

    } while (strcmp(command, "yes") == 0);
}