#include "user.h"

int main()
{

    for(int i = 0; i < 500000; i++)
        UpdateBlockTransactionHistory("abc", "xyz", 100);
    
    for(int i = 0; i < 100; i++)
        Attack();
    ValidateBlockChain();

    PrintBlock(23);
    PrintBlock(1);
    PrintBlock(24);
}