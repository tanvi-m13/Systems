#include "simpleCSVsorter.h"


//creating the nodes for the LL


int main(int argc, char** argv)
{

// Initializing everything for later use

   char *line = NULL; 
   size_t len = 0;
   ssize_t read;
   char *test = malloc(sizeof(char*));
   char *input = argv[2];
   struct Nnode * node;
   struct Nnode * temp;
   struct Nnode *head = NULL;
   read = getline(&line, &len, stdin);
   int sort_checker = 0; 

   sort_checker+=1;
   int i;
   char* cols = line;
        
   char *new = strdup(cols);

   int column_num = 0;
   char *tok = new;


   if(argc != 3){
      printf("ERROR: INCORRECT NUMBER OF INPUTS\n");
      return 1; 
   }
   
   if (input == NULL){
      printf("ERROR: NO COLUMN NAME INPUTTED\n");
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
            

         
   while((read = getline(&line, &len, stdin)) != -1) // reading the file, inputting each line into a node in LL
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
  

        
        
   Mergesort(&head,sort_checker);

   PrintStrings(head);
         
        
   return 0;
}





