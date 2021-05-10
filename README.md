# DSA-project- Blockchain

Blockchain is a program that shows a few functionalites of a block chain network.This Project aims to give you a smaller picture of Bitcoin and in no way a complete
representation of Bitcoin.

&nbsp;

## I. Pre-requisites

You need to install **openssl** library to make this work.
You can install it by using

- `sudo apt-get install libssl-dev`

&nbsp;
## II. Instructions To Run The Program

<br>

### 1. Clone the repo onto your local machine
```
git clone https://github.com/pallavkoppisetti/DSA-project.git
```

### 2. Compile the code
Type in `make` and all the files(.c and .h) will be compiled with the help of a makefile and the object files will be stored in `src/obj`.


### 3. Run the compiled code
```
./blockchain
```
To delete all .o files, run `make clean`.


### 4. Input commands
Once the code is up and running, a menu appears, asking for the input corresponding to the function wished to execute. A command can be chosen from the list of features available.
You can type in `list` for the program to list out all the commands available.

&nbsp;
## III. Features/Commands
<br>

>  Note: The program asks you if you want to continue running it , typing in `No` will exit out of the program and `Yes` will continue running it.

### 1. adduser
Adds a user to our hashtable that stores all of the user info. and assigns a randomly generated ID and prints it out.
The user starts out with a default wallet balance of 1000.

<br>

### 2. transact
Initiates a transaction. Asks for the SenderID, ReceiverID and amount to be transferred.If the transaction is a success, the program adds it to the current block.

> Note: You will face an error if any of the user inputs are invalid.

> Note: The function reptransact is very similar to this function wherein it just repeats the same transaction a certain number of times, which can be decided by the user.

<br>
### 3. reptransact
The function reptransact is very similar to the transact function wherein it just repeats the same transaction a certain number of times, which can be decided by the user.

<br>
### 4. attack

The function performs an attack on the blockchain. Outputs a message which tells whether the attack was successful or not.

<br>

### 5. validateblockchain

This function checks whether any block was attacked prevviously. If it finds that a block was attack, it corrects the block to the original state.

<br>

### 6. userdetails
This function asks for a UserID and prints out all the details of that particular user including wallet balance, jointime , ID and also has an option of view the user's transaction history, provided you give a valid/existing user ID.

<br>

### 7. blockdetails
This function ask for a block number and prints out the details of that particular block such as block number, transactions, previous block hash and nonce.

<br>

### 8. addmultiuser
This function helps us in adding multiple users at once, similar to adduser but here the program asks for how many users we want to add and gives all of them a randomly generated ID.

<br>

### 9. multitransact
This function is very similar to transact, the only difference being that using *multitransact* we can perform multiple transactions at once.

<br>

### 10. list
This function simply lists out all the commands that are available.

<br>

### 11.exit
Exits the program

&nbsp;
