#include "user.h"

int main()
{
    char commands_list[][23] = {"add user", "transact", "attack", "validate blockchain"};
    srand(time(NULL));
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
            long double WalletBalance = 0;

            printf("Please specify amount to be added: ");
            scanf("%g", WalletBalance);
            AddUser(WalletBalance);
        }

        if (strcmp(command, "attack") == 0)
        {
            //function to check with block number
        }

        if (strcmp(command, "transact") == 0)
        {
            //add function to transaction
        }

        printf("Continue (yes/no): ");
        scanf("%s", command);

        printf("\n");

    } while (strcmp(command, "yes") == 0);
}
