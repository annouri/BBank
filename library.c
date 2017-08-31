#include "library.h"
#include <stdio.h>
//Define a user structure
typedef struct User{
    char CIN_user[10];
    char User_full_name[20];
    char User_name[10];
    char User_password[30];
    char User_type;
    struct User *next_user;
}User;
//Define a account structure
typedef struct Account{
    char  Account_CIN_user[10];
    float Account_transaction;
    char  Account_status[10];
}Account;

//Users Management : Functions Prototypes
//initialising User
User *initialise_user();
//Add node to list
User *add_user(User *list_user,User *user);
//Show all users
void show_all_users(User *list_users);
//Show user by CIN
void show_user(User *list_users,char CIN);

//Account Management : Functions Prototypes
//initialising Account
User *initialise_user();
//Add node to list
User *add_user(User *list_user,User *user);
//Show all users
void show_all_users(User *list_users);
//Show user by CIN
void show_user(User *list_users,char CIN);

Account *add_account(Account *list_account,Account *account);

Account *initialise_account();
//Get user by
void hello(void) {

}