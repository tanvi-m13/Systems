
pthread_mutex_t lock; 
char buff[1024]; 
//char input[1024];


struct Address{
   struct sockaddr *addr; 
   socklen_t length;
}Address; 

void signalHandler(int signal);
// This method is a signal method which means every time an user types "Ctrl C", it activates the method and exits the method automatically. 

void input_thread(void* fd);
// This method is reading from the server and printing methods from it. It also lets the user know when the server has been disconnected and exits accordingly. 


void output_thread(void* arg);
//This method prompts the user to choose one of the options in the program every 2 seconds using the sleep method. Whatever the user inputs is then sent to the server and the appropiate method is called to make the client's command work. 





