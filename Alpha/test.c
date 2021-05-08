#include "User data/user.h"

int main()
{
    AddUser(10000);  //Placeholder add user function
    for (int i = 0; i < 100; i++)
        AddUser(1000);

    for (int i = 0; i < 101; i++)
        Transact(0, i, i);
    
    printf("\n");

    for(int i = 1; i < 3; i++)
        PrintBlock(i);
}
