#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
//Define a user structure
typedef struct User{
    char CIN_user[10];
    char User_first_name[10];
    char User_last_name[10];
    char User_password[30];
    char User_type[30];
    struct User *next_user;
}User;
//Define a account structure
typedef struct Transaction{
    char From[10];
    char To[10];
    float transaction;
    struct Transaction *next_transaction;
}Transaction;

//View
void view_login();
void view_user_menu();


//Users Management : Functions Prototypes
    //initialising User
    User *initialise_user();
    //Add node to list
    User *add_user(User *list_user,User *user);
    //Show all users
    void show_all_users(User *list_users);
    //Show user by CIN
    void show_user(User *list_users,char CIN);
    //Import Users DATABASE from File to Memory
    User * load_user_string(char *data);
    User *Load_users_db();
    //Check if user exist
    int check_user(User *list_users,char *CIN);
    //get user total payment
    float get_user_payment(User *list_users,Transaction *list_transactions,char *CIN);
//Account Management : Functions Prototypes
    //initialising Transonacti
    Transaction *initialise_transaction();
    //Add node to list
    Transaction *add_transaction(Transaction *list_transaction,Transaction *transaction);
    //Show all Transactions
    void show_all_transaction(Transaction *list_transaction);
    //Show user by CIN
    void show_all_user_transaction(Transaction *list_transaction,char CIN);
    //Import Users DATABASE from File to Memory
    Transaction * load_transaction_string(char *data);
    Transaction *Load_transactions_db();

User *athentification(User *list_user);
void user_transactions(User *list_users,Transaction *list_transactions,char *CIN);
void user_payment_send(User *list_users,Transaction *list_transactions,char *CIN);
void user_money_received(User *list_users,Transaction *list_transactions,char *CIN);
float get_user_balance(Transaction *list_transactions,char *CIN);
char *get_user_name(User *list_users,char *CIN);
char *get_user_last_name(User *list_users,char *CIN);
void send_money(char *From,char *To,float money);
void send_money_operation(User *list_users,char *From);
void profile(char *name,float balance);
void sign_up();
void main_app();

User *athen(User *list_users,char *cin,char *password);
User *clone_user(User *user);
void view_admin_menu();
//CRYPTIN
int  CryptFile(char *rec,char *des);
int  deCryptFile(char *rec,char *des);
char * decrypte(char *clair);
char * crypting(char *clair);
int main() {
    main_app();
return 0;
}
void main_app(){
    User *list_user=initialise_user();
    list_user=Load_users_db();
    view_login();
    int ch;
    scanf("%d",&ch);
    if(ch==1){
        User *user=initialise_user();

        user=athentification(list_user);
        if(user==NULL){
            printf(RED"Authentication Failed"RESET);
        }
        else if(strcmp(user->User_type,"user\n")==0){
            Transaction *list_transactions=initialise_transaction();
            list_transactions=Load_transactions_db();
            int choix=-1;
            system("clear");
            printf("> user/%s %s\n\n",user->User_last_name,user->User_first_name);
            while (choix!=666){
                view_user_menu();
                scanf("%d",&choix);
                switch(choix){
                    case 1:system("clear");user_transactions(list_user,list_transactions,user->CIN_user);
                        break;
                    case 2:system("clear");user_payment_send(list_user,list_transactions,user->CIN_user);
                        break;
                    case 3:system("clear");user_money_received(list_user,list_transactions,user->CIN_user);
                        break;
                    case 5:system("clear");profile(user->User_first_name,get_user_balance(list_transactions,user->CIN_user));
                        break;
                    case 4:system("clear");if(get_user_payment(list_user,list_transactions,user->CIN_user)>300)
                            printf(BLUE"Transaction Denied"RESET": you have achieved  $300 of Payment\n");
                        else{send_money_operation(list_user,user->CIN_user);list_transactions=Load_transactions_db();}
                            break;
                    case 0:system("clear");exit(0);
                        break;
                    default:
                        break;
                }
            }
        }
        else if(strcmp(user->User_type,"admin\n")==0){
            Transaction *list_transactions=initialise_transaction();
            list_transactions=Load_transactions_db();
            int choix=-1;
            system("clear");
            printf("> admin/%s %s\n\n",user->User_last_name,user->User_first_name);
            while (choix!=666){
                view_admin_menu();
                scanf("%d",&choix);
                switch(choix){
                    case 1:system("clear");show_all_users(list_user);
                        break;
                    case 2:system("clear");show_all_transaction(list_transactions);
                        break;
                    case 3:system("clear");send_money_operation(list_user,user->CIN_user);list_transactions=Load_transactions_db();
                        break;
                    case 0:system("clear");exit(0);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else if(ch==2){
        sign_up();
        main_app();
    }
}
//Users Management : Function Definitions
//initialising User
User *initialise_user(){
    User *user=malloc(sizeof(User));
    strcpy(user->CIN_user,"null");
    strcpy(user->User_first_name,"null");
    strcpy(user->User_last_name,"null");
    strcpy(user->User_password,"null");
    strcpy(user->User_type,"null");
    user->next_user=NULL;
    return user;
};
//Add node to list
User *add_user(User *list_user,User *user){
    if(strcmp(list_user->User_first_name,"null")==0)
        return user;
    else{
        User *temp=initialise_user();
        temp=list_user;
        while(temp->next_user!=NULL){
            temp=temp->next_user;
        }
        temp->next_user=user;
        return list_user;
    }
};
//Show all users
void show_all_users(User *list_users){
    if(strcmp(list_users->User_first_name,"null")==0)
        printf("Db is empty\n");
    else
        printf(BOLDRED"%-20s"RESET,"CIN");
        printf(BOLDRED"%-20s"RESET,"FIRST NAME");
        printf(BOLDRED"%-20s"RESET,"LAST NAME");
        printf(BOLDRED"%-20s"RESET,"PASSWORD");
        printf(BOLDRED"%-20s"RESET,"TYPE");
        printf("\n_____________________________________________________________________________________\n");
    while(list_users!=NULL){
            printf("%-20s",list_users->CIN_user);
            printf("%-20s",list_users->User_first_name);
            printf("%-20s",list_users->User_last_name);
            printf("%-20s","************");
            printf("%-20s",list_users->User_type);
            printf("\n");
            list_users=list_users->next_user;
    }
}
//Load User File To Memory
User * load_user_string(char *data){
    User *user=initialise_user();
    char *token;
    token=strtok(data," ");
    strcpy(user->CIN_user,token);
    token=strtok(NULL," ");
    strcpy(user->User_last_name,token);
    token=strtok(NULL," ");
    strcpy(user->User_first_name,token);
    token=strtok(NULL," ");
    strcpy(user->User_password,token);
    token=strtok(NULL," ");
    strcpy(user->User_type,token);
    return user;

}
User *Load_users_db(){
    deCryptFile("data/db_user.txt","data/user.txt");
    FILE *file_user;
    file_user=fopen("data/user.txt","r");
    char line[300];
    char *token;
    User *list_user=initialise_user();
    if(file_user){
        while(fgets(line,300,file_user)){
            list_user=add_user(list_user,load_user_string(line));
        }
        fclose(file_user);
        CryptFile("data/user.txt","data/db_user.txt");
        return list_user;
}

}


//Transaction Management : Function Definitions
//initialising Transaction
Transaction *initialise_transaction(){
    Transaction *transaction=malloc(sizeof(Transaction));
    strcpy(transaction->From,"null");
    strcpy(transaction->To,"null");
    transaction->transaction=0;
    transaction->next_transaction=NULL;
    return transaction;
};
//Add transaction to list
Transaction *add_transaction(Transaction *list_transaction,Transaction *transaction){
    if(strcmp(list_transaction->From,"null")==0)
        return transaction;
    else{
        Transaction *temp=initialise_transaction();
        temp=list_transaction;
        while(temp->next_transaction!=NULL){
            temp=temp->next_transaction;
        }
        temp->next_transaction=transaction;
        return list_transaction;
    }
};
//Show all Transaction
void show_all_transaction(Transaction *list_transaction){
    if(strcmp(list_transaction->From,"null")==0)
        printf("Db is empty\n");
    else
    printf(BOLDRED"%-20s"RESET,"FROM CIN");
    printf(BOLDRED"%-20s"RESET,"TO CIN");
    printf(BOLDRED"%-20s"RESET,"TRANSACTION");
    printf("\n_____________________________________________________\n");
    while(list_transaction!=NULL){
        printf("%-20s",list_transaction->From);
        printf("%-20s",list_transaction->To);
        printf(GREEN"%.2-20f"RESET,list_transaction->transaction);
        printf("\n");
        list_transaction=list_transaction->next_transaction;
    }
}
//Load Transaction File To Memory
Transaction * load_transaction_string(char *data){
    Transaction *transaction=initialise_transaction();
    char *token;
    token=strtok(data," ");
    strcpy(transaction->From,token);
    token=strtok(NULL," ");
    strcpy(transaction->To,token);
    token=strtok(NULL," ");
    transaction->transaction=atof(token);
    return transaction;

}
Transaction *Load_transactions_db(){
    deCryptFile("data/db_transaction.txt","data/transaction.txt");
    FILE *file_transaction;
    file_transaction=fopen("data/transaction.txt","r");
    char line[300];
    char *token;
    Transaction *list_transaction=initialise_transaction();
    if(file_transaction){
        Transaction *temp=initialise_transaction();
        while(fgets(line,300,file_transaction)){
            list_transaction=add_transaction(list_transaction,load_transaction_string(line));
        }
        fclose(file_transaction);
        CryptFile("data/transaction.txt","data/db_transaction.txt");
        return list_transaction;
    }
}
//Functions ; features OF app
User *clone_user(User *user){
    User *clone=initialise_user();
    strcpy(clone->CIN_user,user->CIN_user);
    strcpy(clone->User_first_name,user->User_first_name);
    strcpy(clone->User_last_name,user->User_last_name);
    strcpy(clone->User_password,user->User_password);
    strcpy(clone->User_type,user->User_type);
    return clone;
}
User *athen(User *list_users,char *cin,char *password){
    while(list_users!=NULL){
        if(strcmp(list_users->CIN_user,cin)==0 && strcmp(list_users->User_password,password)==0){
            return clone_user(list_users);
        }
        list_users=list_users->next_user;
    }
    return NULL;
}
User *athentification(User *list_user){
    printf("\nLogin information\n");
    printf("CIN%-20s",":");
    char cin[30];
    scanf("%s",cin);
    printf("PASSWORD%-15s",":");
    char passord[30];
    scanf("%s",passord);
    User *user=initialise_user();
    user=athen(list_user,cin,passord);
    return user;
}

//Get User Transactions
float get_user_balance(Transaction *list_transactions,char *CIN){
    float balance=0;
    while(list_transactions!=NULL){
        if (strcmp(list_transactions->From,CIN) == 0)
            balance-=list_transactions->transaction;
        else if(strcmp(list_transactions->To,CIN) == 0)
            balance+=list_transactions->transaction;
        list_transactions=list_transactions->next_transaction;
    }
    return balance;
}
float get_user_payment(User *list_users,Transaction *list_transactions,char *CIN) {
    float count=0;
    while (list_transactions!= NULL) {
        if (strcmp(list_transactions->From, CIN) == 0) {
        count+=list_transactions->transaction;
        }
        list_transactions = list_transactions->next_transaction;
    }
    return count;
}
char *get_user_name(User *list_users,char *CIN){
    while (list_users!=NULL){
        if(strcmp(list_users->CIN_user,CIN)==0)return list_users->User_first_name;
        list_users=list_users->next_user;
    }

}
char *get_user_last_name(User *list_users,char *CIN){
    while (list_users!=NULL){
        if(strcmp(list_users->CIN_user,CIN)==0)return list_users->User_last_name;
        list_users=list_users->next_user;
    }

}
void user_transactions(User *list_users,Transaction *list_transactions,char *CIN){
    //Transaction *user_transaction=initialise_transaction();
    printf(BOLDBLUE"All your transactions"RESET"______________________________________________________________________\n\n");
    while(list_transactions!=NULL){
        if (strcmp(list_transactions->From,CIN) == 0){
            printf("%s %-20s%-20s" RED"-""$%.2f\n"RESET,get_user_name(list_users,list_transactions->To),get_user_last_name(list_users,list_transactions->To),"Payment send",list_transactions->transaction);
        }
        else if(strcmp(list_transactions->To,CIN) == 0){
            printf("%s %-20s%-20s" GREEN"+""$%.2f\n"RESET,get_user_name(list_users,list_transactions->From),get_user_last_name(list_users,list_transactions->From),"Money received",list_transactions->transaction);
        }


        list_transactions=list_transactions->next_transaction;
    }
    printf("_____________________________________________________________________________\n\n");
}
void user_money_received(User *list_users,Transaction *list_transactions,char *CIN){
    //Transaction *user_transaction=initialise_transaction();
    printf(BOLDBLUE"Money received"RESET"______________________________________________________________________\n\n");
    while(list_transactions!=NULL){
        if (strcmp(list_transactions->To,CIN) == 0){
            printf("%s %-20s%-20s" GREEN"+""$%.2f\n"RESET,get_user_name(list_users,list_transactions->From),get_user_last_name(list_users,list_transactions->From),"Money received",list_transactions->transaction);
        }
        list_transactions=list_transactions->next_transaction;
    }
    printf("_____________________________________________________________________________\n\n");
}
void user_payment_send(User *list_users,Transaction *list_transactions,char *CIN){
    //Transaction *user_transaction=initialise_transaction();
    printf(BOLDBLUE"Payment send"RESET"______________________________________________________________________\n\n");
    while(list_transactions!=NULL){
        if (strcmp(list_transactions->From,CIN) == 0){
            printf("%s %-20s%-20s" BOLDRED"-""$%.2f\n"RESET,get_user_name(list_users,list_transactions->To),get_user_last_name(list_users,list_transactions->To),"Payment send",list_transactions->transaction);
        }
        list_transactions=list_transactions->next_transaction;
    }
    printf("_____________________________________________________________________________\n\n");
}
void send_money_operation(User *list_users,char *From){
    printf("Receiver CIN%-20s",":");
    char receiver[30];
    scanf("%s",receiver);
    if(check_user(list_users,receiver)==0){
        printf("Total%-15s",":");
        float money;
        scanf("%f",&money);
        send_money(From,receiver,money);
        printf(GREEN"Money Send\n"RESET);
    } else{
        printf(RED"Invalid User\n"RESET);
    }

}
void send_money(char *From,char *To,float money){
    deCryptFile("data/db_transaction.txt","data/transaction.txt");
    FILE *file_transaction;
    file_transaction=fopen("data/transaction.txt","a");
    if(file_transaction){
        fprintf(file_transaction,"%s %s %0.2f\n",From,To,money);
        fclose(file_transaction);
    }
    CryptFile("data/transaction.txt","data/db_transaction.txt");
}
void sign_up(){
    FILE *file_user;
    file_user=fopen("data/user.txt","a");
    printf("Account infromation :\n");
    printf("%-20s","CIN:");
    char cin[30];
    scanf("%s",cin);
    printf("%-20s","First name:");
    char first_name[30];
    scanf("%s",first_name);
    printf("%-20s","Last name:");
    char last_name[30];
    scanf("%s",last_name);
    printf("%-20s","Password:");
    char password[30];
    scanf("%s",password);
    if(file_user){
        fprintf(file_user,"%s %s %s %s %s\n",cin,last_name,first_name,password,"user");
        fclose(file_user);
    }
    printf("Account created !\n");
}
int check_user(User *list_users,char *CIN){
    while(list_users!=NULL){
        if(strcmp(list_users->CIN_user,CIN)==0)return 0;
        list_users=list_users->next_user;
    }
    return 1;
}
//Views

void view_login(){
    printf("  ____  _         ____              _    \n"
                   " |  _ \\(_)       |  _ \\            | |   \n"
                   " | |_) |_  __ _  | |_) | __ _ _ __ | | __\n"
                   " |  _ <| |/ _` | |  _ < / _` | '_ \\| |/ /\n"
                   " | |_) | | (_| | | |_) | (_| | | | |   < \n"
                   " |____/|_|\\__, | |____/ \\__,_|_| |_|_|\\_\\\n"
                   "           __/ |                         \n"
                   "          |___/                          \n");
    printf("                _ _.-'`-._ _\n"
                   "               ;.'________'.;\n"
                   "    _________n.[____________].n_________\n"
                   "   |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]\n"
                   "   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|\n"
                   "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
                   "   |.. .. .. ..||..||..||..||.. .. .. ..|\n"
                   "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|\n"
                   ",,;;,;;;,;;;,;;;,;;;,;;;,;;;,;;,;;;,;;;,;;,,\n");

    printf("%15s %20s","1- Login","2-Sign up\n\n");
}
void view_admin_menu(){
    printf(BOLDBLUE"MENU"RESET"______________________________________________________________________\n\n");
    printf("%-20s %-20s %-20s %-20s\n","1-All Users","2-All Transactions","3-Power account","0-Exit");
    printf("_____________________________________________________________________________\n\n");
}
void profile(char *name,float balance){
    printf(".%-40s",name);
    printf(BOLDBLUE"%20s"RESET,"Blance Available :\t");
    printf("$%.2f"BOLDGREEN"%s"RESET,balance,"USD");
}
void view_user_menu(){
    printf("\n\n"BOLDBLUE"MENU"RESET"_______________________________________________________________________________________\n\n");
    printf("%-20s %-20s %-20s %-20s %-20s %-20s\n","1-Transactions","2-Payment send","3-Money received","4-New payment","5-Balance","0-Exit");
    printf("________________________________________________________________________________________________\n\n");
}
void crypt_file(char *rec,char *des){
    User *list_user=Load_users_db();
    FILE *file_user;
    file_user=fopen("data/user.txt","a");
    char line[300];
    char *token;
    if(file_user){
        while(list_user!=NULL){
            fprintf(file_user,"%s %s %s %s %s\n",list_user->CIN_user,list_user->User_last_name,list_user->User_first_name,list_user->User_password,list_user->User_type);
        }}
        fclose(file_user);

}
int  deCryptFile(char *rec,char *des){
    FILE *file=NULL;
    FILE *file1=NULL;
    char array[100];
    file=fopen(rec,"r");
    file1=fopen(des,"a+");
    if (file!=NULL){
        if(file1!=NULL)
            while(fgets(array,100,file)!=NULL)
            {
                fputs(decrypte(array),file1);
            }

        fclose(file);
        fclose(file1);
        remove(rec);
        return 0;
    }
    return 1;
}
int  CryptFile(char *rec,char *des){
    FILE *file=NULL;
    FILE *file1=NULL;
    char array[100];
    file=fopen(rec,"r");
    file1=fopen(des,"a");
    if (file!=NULL){
        if(file1!=NULL)
            while(fgets(array,100,file)!=NULL)
            {
                fputs(crypting(array),file1);
            }

        fclose(file);
        fclose(file1);
        remove(rec);
        return 0;
    }
    return 1;
}
char * decrypte(char *clair) {
    int i = 0;
    while (clair[i] != NULL) {
        clair[i] -= 5;
        i++;
    }
    return clair;
}
char * crypting(char *clair){
    int i=0;
    while(clair[i]!=NULL){
        clair[i]+=5;
        i++;
    }
    return clair;
}
