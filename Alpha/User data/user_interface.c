#include "user.h"

int main()
{
    char commands_list[][23] = {"add user", "transact", "attack", "validate blockchain"};

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

        if (strcmp(command, "add user") == 0)
        {
            char ID[10];
            //RandomID(ID);
            //function to add to database
        }

        if (strcmp(command, "attack") == 0)
        {
            //function to check with block number
        }

        printf("Continue (yes/no): ");
        scanf("%s", command);

        printf("\n");

    } while (strcmp(command, "yes") == 0);
}
