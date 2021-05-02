#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/////////////////////////////
//JUST FOR TESTING PURPOSES//
////////////////////////////


typedef struct userinfo
{
    char ID[25];
    long ArrayID;   //stores the position of user node in the UserData array
    long long int balance;
    char JoinDateTime[50];

} User;

long NumberOfUsers = 0;
User* UserData = NULL;

bool AddUser(long long WalletBalance)
{   
    time_t t;
    time(&t);

    if(UserData == NULL)
        UserData = (User*) calloc(10, sizeof(User));  //Initial size of 100 users;
    if(NumberOfUsers * 2 > sizeof(UserData)/sizeof(User))
        UserData = (User*)realloc(UserData, 2 * NumberOfUsers * sizeof(User));

    UserData[NumberOfUsers].ArrayID = NumberOfUsers;
    strcpy(UserData[NumberOfUsers].JoinDateTime, ctime(&t));
    UserData[NumberOfUsers].balance = WalletBalance;
    //strcpy(UserData[NumberOfUsers].ID, RandomID());

    NumberOfUsers++;
}

int main()
{
    for(int i = 0; i < 50; i++)
        AddUser(i * 10000);
    
    for(int i = 0; i < NumberOfUsers; i++)
    {
        printf("%ld\t", UserData[i].ArrayID);
        printf("%lld\t", UserData[i].balance);
        printf("%s\n", UserData[i].JoinDateTime);

    }
}