#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include "bankingServer.h"



void quit(int sD, account * account) 
{
    char Msg[500];
    account->session = 0;
    strcpy(Msg, "You have exited the bank.\n\n");
    write(sD, Msg, sizeof(Msg)-1);
    printf("A client has disconnected from the server.\n");
    //pthread_mutex_unlock(&acc->accountLock);
}


void endAccount(int sD, account * account) 
{
    char Msg[500];
    account->session = 0;
    strcpy(Msg, "You have successfully ended your session.\n\n");
    write(sD, Msg, sizeof(Msg)-1);
    //pthread_mutex_unlock(&acc->accountLock);
}


void query(int sD, account * account) 
{

    char Msg[500];
    sprintf(Msg, "Your account balance is $%.2f.\n\n", account->balance);
    write(sD, Msg, sizeof(Msg)-1);

}


void deposit(int sD, account * account, double value)
{
    char Msg[500];
    
    account->balance += value;
    sprintf(Msg, "You have successfully deposited $%.2f to your account.\n\n", value);
    write(sD, Msg, sizeof(Msg)-1);
}

void withdraw(int sD, account * account, double value) {
    
    if (account->balance < value) {
        char Msg[500];
        strcpy(Msg, "The amount you entered is more than your balance. You may not withdraw this from your account.\n\n");
        write(sD, Msg, sizeof(Msg)-1);
    }

    else {
        char Msg[500];
        account->balance -= value;
        sprintf(Msg, "You have successfully withdrawn $%.2f from your account.\n\n", value);
        write(sD, Msg, sizeof(Msg)-1);
    }
}

account * serveAccount(int sD, char AccName []) 
{

        char Msg[1000];  

        int i;

          for (i = 0; i < XCount; i++) 
            {
                
                if (strcmp(accounts[i].acctName, AccName) == 0) {
                    break;
                }

            } 
          if(XCount == i)
          {
                sprintf(Msg, "The account: %s does not exist... \n", AccName);
                write(sD, Msg, sizeof(Msg)-1);
                return NULL;
          }
          
          else
          {
                accounts[i].session = 1;
                strcpy(Msg, "You have successfully started a session.\n\n");
                write(sD, Msg, sizeof(Msg)-1);
                return &accounts[i];
          }
            
            
          
            
            
}

void createAccount(int sD, char AccName[])
{       
        
        char Msg[1000];
        int i;
        //printf("hi, XCOUNT is %d\n", XCount);
        if(XCount == 0)
        {       
                //accounts[0].acctName = AccName;
                accounts[0].acctName = malloc(strlen(AccName)+1);
                strcpy(accounts[0].acctName, AccName);
                //printf("Debug\n");
                accounts[0].balance = 0;
                accounts[0].session = 0;
                XCount++;
                sprintf(Msg, "The account: %s that you have requested has been created. \n", AccName);
                write(sD, Msg, sizeof(Msg)-1);
                return;
        } 
        else
        {
                for(i=1;i<XCount; i++)
                {
                        if(strcmp(accounts[i].acctName, AccName) == 0)
                        {
                                strcpy(Msg, "The account already exists...");
                                write(sD, Msg, sizeof(Msg)-1);
                                return;
                        }
                        
                
                }
                
                pthread_mutex_lock(&lock);
                
                accounts[i].acctName = malloc(strlen(AccName)+1);
                strcpy(accounts[i].acctName, AccName);
                accounts[i].balance = 0;
                accounts[i].session = 0;
                XCount++;
                sprintf(Msg, "The account: %s that you have requested has been created. \n", AccName);
                
                pthread_mutex_unlock(&lock);
                write(sD, Msg, sizeof(Msg)-1);
                return;
        }
}







//method prints list of accounts every 15 seconds
void pausee(){

while(1)
{
   int i; 
   printf("ACCOUNTS: \n");
   printf("_______________________________\n");
      for (i = 0; i < XCount; i++) 
                {
                            printf("Account name: %s\t", accounts[i].acctName);
                            printf("Current Balance: $%.2f\t", accounts[i].balance);
                            if (accounts[i].session == 1){
                                printf("IN SERVICE");
                           }
                           
                            printf("\n");
                }
      sleep(15);

}

}



//a client thread for each connection
void* client_connection(void *socketfd)
{  
        printf("Client Accepted!\n");
        sockd = *(int *) socketfd;
        char buffer[500];
        char response[500];
 while (recv(sockd, buffer, sizeof(buffer)-1, 0) > 0) {
   char command[500];
   char nameOrVal[100];
   sscanf(buffer, "%s %[^\n]", command, nameOrVal);
   
   
   if(strcmp(command, "create") == 0)
        {
       
       
                if (TempAcct != NULL && TempAcct->session != 0)
                        {

                             strcpy(response, "You are already logged into an account. You may not serve or log into an account.\n\n");
                             send(sockd, response, sizeof(response)-1, 0);

                        }
                        else
                        {
                                createAccount(sockd, nameOrVal);
                        }
       
       
        }
 
      else if(strcmp(command, "serve") == 0)
        {
       
       
                if (TempAcct != NULL && TempAcct->session != 0)
                {

                     strcpy(response, "You are already logged in. You may not serve another account.\n\n");
                     send(sockd, response, sizeof(response)-1, 0);

                }
                else
                {
       
                        TempAcct = serveAccount(sockd, nameOrVal);
                }
        }
 
 
      else if (strcmp(command, "deposit") == 0)
        {
       
                if (strlen(nameOrVal) == 0)
                {
                strcpy(response, "You have not entered a value.\n\n");
                send(sockd, response, sizeof(response)-1, 0);
                continue;
                }
       
                if (TempAcct == NULL || TempAcct->session == 0) {

                strcpy(response, "You are not logged in. You may not deposit at this time.\n\n");

                send(sockd, response, sizeof(response)-1, 0);
                }
       
        
       
                else
                {
               
                        double val = atof(nameOrVal);

                        double round = roundf(val*100)/100;

                        if ((fabs(round - 0.0f) < 0.00001) || (round < 0.0f)) {
                           
                            strcpy(response, "The value that you have entered is invalid.\n\n");

                            send(sockd, response, sizeof(response)-1, 0);

                        }

                        else {

                            deposit(sockd, TempAcct, round);

                        }
               
                }
       
       
       
       
       
       }
       
       else if (strcmp(command, "withdraw") == 0)
        {      
                if (strlen(nameOrVal) == 0)
                {
                strcpy(response, "You have not entered a value.\n\n");
                send(sockd, response, sizeof(response)-1, 0);
                continue;
                }
                if (TempAcct == NULL || TempAcct->session == 0)
                {

                        strcpy(response, "You are not logged in. You may not withdraw at this time.\n\n");

                        send(sockd, response, sizeof(response)-1, 0);
       
                }
       
                else
                {
               
                        double val = atof(nameOrVal);

                        double round = roundf(val*100)/100;

                        if ((fabs(round - 0.0f) < 0.00001) || (round < 0.0f)) {
                           
                            strcpy(response, "The value that you have entered is invalid.\n\n");

                            send(sockd, response, sizeof(response)-1, 0);

                        }

                        else {

                            withdraw(sockd, TempAcct, round);

                        }
               
                }
       
       
         }
         else if (strcmp(command, "query") == 0)
         {

            if (TempAcct == NULL || TempAcct->session == 0) {

                strcpy(response, "You are not logged in. You do not have access to an account balance at this time.\n\n");

                send(sockd, response, sizeof(response)-1, 0);

            }


            else {

                query(sockd, TempAcct);

            }

        }
        
       else if (strcmp(command, "end") == 0) 
        {

            if (TempAcct == NULL || TempAcct->session == 0) {

                strcpy(response, "You are not logged in. You cannot end a session at this time.\n\n");

                send(sockd, response, sizeof(response)-1, 0);

            }
            

            else {

                endAccount(sockd, TempAcct);

            }

        }
        else if (strcmp(command, "quit") == 0) {
           
            if (TempAcct == NULL) {

                strcpy(response, "You have quit bank.\n\n");
                send(sockd, response, sizeof(response)-1, 0);

                printf("A client has disconnected from the server.\n");

                close(sockd);

                break;

            }
            

            else {

                quit(sockd, TempAcct);

                close(sockd);

                break;

            }

        }
        
        else {

            strcpy(response, "The command that you have entered is not valid. Please try again.\n\n");

            send(sockd, response, sizeof(response)-1, 0);

        }
        
        memset(command, '0', sizeof(command));
        memset(nameOrVal, '0', sizeof(nameOrVal));
        memset(buffer, '0', sizeof(buffer));
        memset(response, '0', sizeof(response));
        
       
 }//while



}

        
//Accepts all of the Clients       
void new_session(){
   int addrlen = -1; 
   //pthread_t clients[100000]; 
   struct sockaddr_in client; 
   
   if(listen(server_fd,100)<0){
      printf("ERROR: Unable to Listen. \n"); 
      exit(1);
   }
   
   addrlen = sizeof(client); 
   
   while(1){
      sockd = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen);
      connections++; 
      pthread_t clients[connections]; 
      printf("Client %d has connected to Server. \n",connections); 
      if(pthread_create(&clients[connections],NULL,client_connection,(void*)&sockd)<0){
         printf("Error: Could not create thread. \n"); 
         exit(1); 
      }
  }
                       
                     
                       
}

int main(int argc, char **argv){

   XCount--;

   pthread_t printtt,client;
  
   
   if(argc != 2){
      printf("ERROR: Incorrect number of inputs. \n"); 
      exit(1); 
   }
   
    
    struct sockaddr_in address; 
    int port = atoi(argv[1]); 
    int opt = 1; 

       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port  
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 
       
    // Forcefully attaching socket to the port  
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    if(pthread_create(&client,NULL,(void*)new_session,NULL)<0){
      printf("ERROR: Failed to Create thread. \n"); 
      exit(1); 
    }
    
    if(pthread_create(&printtt,NULL,(void*)pausee,NULL)<0){
      printf("Error: Failed to create Thread. \n"); 
      exit(1); 
    }
    pthread_join(printtt, NULL);  
    pthread_join(client, NULL); 
   close(server_fd);
   return 1;
}
