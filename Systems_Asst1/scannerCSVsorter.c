#include "scannerCSVsorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>


//creating the nodes for the LL


int x = 1;
int r[255];
 



int isCSV(char *directoryName){
   char *extension; 
   extension = strrchr(directoryName,'.');
   if((extension != NULL)&&(strcmp(extension,".csv") == 0)){
     // printf("1\n");
      return 1; 
   }
   else{
      return 0; 
   }
   
}



int sorting(char *file,char *colName,char* dirOut){


// Initializing everything for later use
   const char *scheck = "-sorted-";
   char *alreadySorted;

   alreadySorted = strstr(file, scheck);
   if (alreadySorted)
   {
       return 1;
   }
   FILE *filename = fopen(file,"r");
   
   char *line = NULL; 
   size_t len = 0;
   ssize_t read;
   char *test = malloc(sizeof(char*));
   char *input = colName;
   struct Nnode * node;
   struct Nnode * temp;
   struct Nnode *head = NULL;

   read = getline(&line, &len, filename); //column names (first row)

   int sort_checker = 0; 
   sort_checker+=1;
   int i;
   char* cols = line;    
   char *new = strdup(cols);
   int column_num = 0;
   char *tok = new;

   if(filename == NULL){
      printf("ERROR: COULD NOT OPEN FILE\n"); 
      return 1; 
   }
  
   //Finding the column that should be sorted from user input
      while(tok != NULL)
      {  
         if(strcmp(tok, input) ==0)
         {
            break;
         }
         else{
         tok = strsep(&new,",");
         column_num++;
         }
      }
    if(tok == NULL){
      printf("ERROR: INVALID COLUMN NAME\n");
      return 1; 
     }
         

        //Checking if the input is an int or a double or a char
        
   if( strcmp(input ,"color")==0)
      sort_checker = 0; 
   else if(strcmp(input ,"director_name")==0)
      sort_checker = 0;
   else if(strcmp(input , "num_critic_for_reviews")==0)
      sort_checker =1; 
   else if(strcmp( input , "duration")==0)
      sort_checker =1; 
   else if(strcmp( input , "director_facebook_likes")==0)
      sort_checker =1; 
   else if( strcmp(input , "actor_3_facebook_likes")==0)
      sort_checker =1; 
   else if(strcmp( input , "actor_2_name")==0)
      sort_checker =0; 
   else if( strcmp(input , "actor_1_facebook_likes")==0)
      sort_checker =1; 
   else if(strcmp( input , "gross")==0)
      sort_checker =1; 
   else if(strcmp( input , "genres")==0)
      sort_checker =0; 
   else if( strcmp(input , "actor_1_name")==0)
      sort_checker =0; 
   else if( strcmp(input , "movie_title")==0)
      sort_checker =0; 
   else if( strcmp(input , "num_voted_users")==0)
      sort_checker =1; 
   else if( strcmp(input , "cast_total_facebook_likes")==0)
      sort_checker =1; 
   else if(strcmp( input , "actor_3_name")==0)
      sort_checker =0; 
   else if( strcmp(input , "facenumber_in_poster")==0)
      sort_checker =1; 
   else if( strcmp(input , "plot_keywords")==0)
      sort_checker =0; 
   else if(strcmp( input , "movie_imdb_link")==0)    
      sort_checker =0; 
   else if( strcmp(input , "num_user_for_reviews")==0)
      sort_checker =1; 
   else if( strcmp(input , "language")==0)
      sort_checker =0; 
   else if( strcmp(input ,"country")==0)
      sort_checker =0; 
   else if(strcmp( input , "content_rating")==0)
      sort_checker =0; 
   else if( strcmp(input , "budget")==0)
      sort_checker =1; 
   else if( strcmp(input , "title_year")==0)
      sort_checker =1; 
   else if(strcmp( input , "actor_2_facebook_likes")==0)
      sort_checker =1; 
   else if( strcmp(input , "imdb_score")==0)
      sort_checker =2; 
   else if( strcmp(input , "aspect_ratio")==0)
      sort_checker =2; 
   else if(strcmp(input , "movie_facebook_likes")==0)
      sort_checker =1; 
            
   //reading the file, inserting each line into the linked list as well as the value that should be sorted
    
   while((read = getline(&line, &len, filename)) != -1) // reading the file, inputting each line into a node in LL
   {  
      test = malloc(sizeof(char*));
      test = line; 
      temp = malloc(sizeof(struct Nnode));
      temp->data = malloc(strlen(test)+1);
      temp->
      val_sort = malloc(strlen(test)+1);
      strcpy(temp->data,test);

      char* z = strdup(test);
      for(i=0;i<column_num;i++) //inserting the value that should be sorted into node->val_sort
      {  
         tok = strsep(&z,",");
         if(i == column_num-1)
         {
            strcpy(temp->val_sort,tok);            
         }             
      }
      temp->next = NULL; 
            
      //INSERTION
      if(head == NULL) // head pointer which does not change--> will only go inside this once
      {
         head = temp;
      }


      else //for the rest of the body nodes
      {
         node = head;
         while(node->next != NULL)
         {
           node = node->next;
         }//end this while loop
         
         node->next = temp;
      } 
           
   }//close first while loop 

   free(line);
   Mergesort(&head,sort_checker);
   
   
   PrintStrings(head,input,file,dirOut);
         
        
   return 0;
}
void readDirectory(char *inputDir, char *outputDir, char *sortField, char*srcDir) 
{
   
   DIR *dir;
   struct dirent *sd;
   dir = opendir(inputDir);
   if(dir == NULL)
   {
   printf("ERROR: Invalid Directory\n");
   return;
   
   }
   
   
   

    while ((sd = readdir(dir)) != NULL) {
        if (sd->d_name[0] == '.') {
            continue;
        }
       
        if(sd->d_type == DT_DIR){
        char* actualDirPath = malloc(PATH_MAX+1);
        strcpy(actualDirPath, inputDir);
        strcat(actualDirPath, "/");
        strcat(actualDirPath, sd->d_name);

        int pID = fork();
        if(pID == 0){
        fflush(stdout);
        break;
        }
        else
        {  
           
            readDirectory(actualDirPath,outputDir,sortField, srcDir);
        }
       }
       
       
        if(isCSV(sd->d_name) == 1){

        char* actualCSVPath = malloc(PATH_MAX+1);
        strcpy(actualCSVPath, inputDir);
        strcat(actualCSVPath, "/");
        strcat(actualCSVPath, sd->d_name);


        int pID = fork(); //pID
               if(pID == 0)//child process
              {
              

               sorting(actualCSVPath,sortField,outputDir);

               exit(0);
               break;
               }
          else{
              //printf("PID = %d\n",pID);
              }
        }
       
      
    }
    closedir(dir);
    int pid;
    

    int status = 0;
    while ((pid = wait(&status)) != -1) {
        r[x] = pid;
        x++;
        
         
    }
    
   
    }



int main(int argc, char** argv)
{
   char *input; 
   char *dirIn =NULL ; 
   char *dirOut =NULL;
 
 
 
 if(argc == 3 || argc ==5 || argc == 7) 
   {
      //Correct Number of Inputs
   }
   
  else
  {
  printf("ERROR:Incorrect number of arguments\n");
  return 1;
  }   
   int i; 
   for(i =1;i<argc; i = i+2){
      char *option = argv[i];
      if(strcmp(option,"-c") == 0)
      {
         input = argv[i+1];
      }
      else if(strcmp(option,"-d") == 0)
      {
         dirIn = argv[i+1];
      }
      else if (strcmp(option, "-o")==0)
      {
         dirOut = argv[i+1];
      }
      else
      {
         printf("ERROR:Invalid Parameter\n");
         return 1; 
      }
      
      
      
      
    }
     if(dirIn==NULL)
    {
        dirIn = ".";
    } 
    
    
    if(dirOut!=NULL && strcmp(dirOut, ".")!=0)
    {
    mkdir(dirOut, 0700);
    }
    
    if(dirOut==NULL)
    {
        dirOut = ".";
    }
    
    char*path = realpath(dirOut,NULL);
    int parentPID = getpid();
    r[0] = parentPID;
    printf("Initial PID: %d\n",getpid());
   
    char*srcDir = realpath(dirIn,NULL);

   
    readDirectory(dirIn, path,input,srcDir);
    if(getpid() == parentPID){
   
    int count = 1;
    printf("PIDS of All Child Processes: ");
    printf("%d", r[count]);
    count++;
    while(count < x)
    {
    printf(", %d", r[count]);
    count++;
    }
    printf("\n");
    printf("Total Number of Processes: %d\n", (x-1));
    }
        return 1;

}



