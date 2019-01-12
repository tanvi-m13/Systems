typedef struct Account
{
   char *acctName;
   double balance;
   int session;      //1 = IN SERVICE, 0 = NOT IN SERVICE
   
} account;




int XCount=1;
int server_fd;
int connections =0; 


account accounts[99999];



pthread_mutex_t lock;


account* TempAcct = NULL;




int sockd;



void quit(int sD, account * account);
//This completely disconnects the client from the server. 


void endAccount(int sD, account * account);
//This makes an account that is in service go offline. 


void query(int sD, account * account);
//This returns the current balance of the account that is online. 


void deposit(int sD, account * account, double value);
//This deposits money into the bank server.



void withdraw(int sD, account * account, double value);
//This takes money out of the account that is currently active.


account * serveAccount(int sD, char AccName []);
//This makes an innactive account into an active account. 



void createAccount(int sD, char AccName[]);
//This creates a new account and adds it to the array of accounts in the server.



void pausee();
//This Prints out the current accounts and their statuses every 15 seconds. 


void* client_connection(void *socketfd);
//This communicates with the client and takes in all the commands and calls the function that is needed. 



void new_session();
//This accepts every client that connects to the server and makes a new thread for each client
