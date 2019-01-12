#include <stdio.h>
#include <stdlib.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>
#include "bankingClient.h"
#define MAX 256 
#define PORT 9365 
#define SA struct sockaddr
int sockfd =0; 
pthread_mutex_t lock; 
char buff[1024]; 



void signalHandler(int signal) 
{ 
    printf("You have ended the program. \n"); 
    exit(0); 
} 

 
// input thread is reading from server and printing messages from it.  
void input_thread(void* fd){

   char input[MAX]; 
   int dest = *(int *)fd; 
   
   int ptr; 
   
   while((ptr = read(dest, input, sizeof(input)-1)) > 0){
   
      printf("%s",input); 
      memset(input, '\0', sizeof(input)); 
   }
   
   if(ptr == 0){
      printf("You have been Disconnected. \n"); 
      exit(1); 
   }

  
 }  //method   
 
// output thread prompts the user to choose from the options every 2 seconds, reads from stdin and writes it to server 
void output_thread(void* arg){
   char output[MAX]; 
   int dest = *(int *)arg; 
   int ptr2; 
   
   printf("Please enter any of the following commands. \n"); 
   printf("create<accountname(char)>: creates a new account. \n"); 
   printf("serve<accountname(char)> : starts a service session.\n"); 
   printf("deposit<amount(double)> : adds amount to bank balance.\n");
   printf("withdraw<amount(double)>: subtracts amount from bank balance. \n"); 
   printf("query: return the balance.\n"); 
   printf("end: end a current session. \n"); 
   printf("quit: to exit the program. \n"); 
   
   while((ptr2 = read(0,output,sizeof(output)-1))> 0){
      int t = write(dest, output, sizeof(output)-1); 
      if (t==0){
         printf("ERROR: Disconnected. \n"); 
         exit(1); 
      }
      printf("Please enter any of the following commands. \n"); 
      printf("create<accountname(char)>: creates a new account. \n"); 
      printf("serve<accountname(char)> : starts a service session.\n"); 
      printf("deposit<amount(double)> : adds amount to bank balance.\n");
      printf("withdraw<amount(double)>: subtracts amount from bank balance. \n"); 
      printf("query: return the balance.\n"); 
      printf("end: end a current session. \n"); 
      printf("quit: to exit the program. \n"); 
      sleep(2); 
   }//while
   
}//method
  
int main(int argc, char ** argv) 
{ 

    if (argc != 3){
      printf("ERROR: invalid number of inputs\n"); 
      exit(1); 
    }
   int sockfd = 0;
    struct sockaddr_in serv_addr; 
    int port = atoi(argv[2]); 

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
    
   struct hostent *hp; 
   struct in_addr **addr_list; 
   int i; 
   char *hostname = argv[1];
   char ip[100];

   if((hp=gethostbyname(hostname))==NULL){
      printf("ERROR.\n"); 
      return 1; 
   }
   
   addr_list = (struct in_addr **)hp->h_addr_list;
   for(i=0; addr_list[i] != NULL; i++){
      strcpy(ip,inet_ntoa(*addr_list[i])); 
       
   }
   

       
   //converts IP address
    if(inet_pton(AF_INET,ip , &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
  
    //signal handler
    signal(SIGINT, signalHandler); 
    
    
    
    // connect the client socket to server socket 
    while (1){
        printf("Establishing connection with server...\n"); 
        if(connect(sockfd, (SA*)&serv_addr, sizeof(serv_addr)) < 0) { 
            sleep(3); 
         }
         else{
         printf("Connected. Port: %d IP Address: %s\n",port,ip); 
         break;
         }
    } 
    

    

  
   if(pthread_mutex_init(&lock,NULL)!= 0){
      printf("ERROR: Mutex failed. \n"); 
   }
   
   //waits for response from server
    pthread_t output; 
    //waits for input from user
    pthread_t input; 
    
    
    int z = pthread_create(&output,0,(void*)output_thread,(void*)&sockfd); 
    if(z != 0){
      printf("ERROR: Failed to create thread. \n"); 
      exit(1); 
    }
    int h =pthread_create(&input,0,(void*)input_thread,(void*) &sockfd); 
    if(h != 0){
      printf("ERROR: Failed to create thread.\n"); 
      exit(1); 
    }
    
    
    pthread_join(input, NULL); 
    printf("Client process Ended. \n");
    
    pthread_mutex_destroy(&lock);  
    close(sockfd); 

    return 0; 
}




 
 
