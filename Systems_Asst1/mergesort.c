#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scannerCSVsorter.h"



void Split(struct Nnode* Head, struct Nnode **front, struct Nnode **back){ 
//this method is supposed to find the middle node in the list to split it up from
//Example: 10-->5-->43-->3
//In the end, front = 10
// back = 43
//So in the end, it splits it into two LLs, 10-->5 and 43-->3

//USING THE FAST-SLOW METHOD
   struct Nnode *fast, *slow; 
   struct Nnode *head = Head; 
   if((head == NULL) || (head->next == NULL)){
      *front = head; 
      *back = NULL; 
      return; 
   }
   else{
   slow = Head; 
   fast = Head->next; 
   
   while(fast != NULL){
      fast = fast->next; 
      if(fast != NULL){
         fast = fast->next; 
         slow = slow->next; 
       }
    }
    
    *front = Head; 
    *back = slow->next; 
    slow->next = NULL; 
    }
    
 }
 



struct Nnode* SortingInts(struct Nnode *Half1, struct Nnode *Half2){ //sorts the LL by INTEGERS/DOUBLES, recursive call to keep sorting
   struct Nnode *root = NULL; 
      if(Half1 == NULL){
         return Half2; 
      }
      if(Half2== NULL){
         return Half1; 
      }
      if(atoi(Half1->val_sort) <= atoi(Half2->val_sort)){
         root = Half1; 
         root->next = SortingInts(Half1->next, Half2); 

      }
      else{
         root = Half2; 
         root->next = SortingInts(Half1,Half2->next);
      }
     
    return root; 
    
}

struct Nnode* SortingDoubles (struct Nnode *Half1,struct Nnode *Half2){//sorts LL through strcmp with STRINGS
   struct Nnode *root = NULL; 
   if(Half1 == NULL){
      return Half2; 
   }
   if(Half2== NULL){
      return Half1; 
   }
      if(atof(Half1->val_sort) <= atof(Half2->val_sort)){      
         root = Half1; 
         root->next = SortingDoubles(Half1->next, Half2); 
      }
      else{
         root = Half2; 
         root->next = SortingDoubles(Half1,Half2->next);
      }
     
    return root; 
    
    }


struct Nnode* SortingStrings(struct Nnode *Half1,struct Nnode *Half2){//sorts LL through strcmp with STRINGS
   struct Nnode *root = NULL; 
   if(Half1 == NULL){
      return Half2; 
   }
   if(Half2== NULL){
      return Half1; 
   }
      if(strcmp(Half1->val_sort,Half2->val_sort)<0){      
         root = Half1; 
         root->next = SortingStrings(Half1->next, Half2); 
      }
      else{
         root = Half2; 
         root->next = SortingStrings(Half1,Half2->next);
      }
     
    return root; 
    
    }



void PrintStrings (struct Nnode*node, char* input,char *filename, char *dirOut){
   
   char * File;
   const char character = '/';

   File = strrchr(filename, character);
   


   if (File[0] == '/') {
    memmove(File, File+1, strlen(File));
    }
   //printf("fileName Print: %s\n", File);
   char  *fileName = malloc(strlen(File)+1);
   strcpy(fileName, File);
   char *newfile = malloc(strlen(fileName)-3);
   memcpy(newfile, fileName, strlen(fileName)-4);
   
   char *column = malloc(strlen(input) +1);
   strcpy(column, input);
   char* csv = malloc(strlen(column) + strlen(".csv") + 1);
   strcpy(csv, column);
   strcat(csv, ".csv");
   char * sort = malloc(strlen(csv) + strlen("-sorted-") + 1);
   strcpy(sort,"-sorted-");
   strcat(sort, csv);
   
   char * newFileName = malloc(strlen(newfile) + strlen(sort) + 1);
   strcpy(newFileName, newfile);
   strcat(newFileName, sort);
   char *outFileName = malloc(strlen(dirOut) + strlen(newFileName) + 2);
   strcpy(outFileName, dirOut);
   strcat(outFileName, "/");
   strcat(outFileName, newFileName);
   FILE* output = fopen(outFileName, "w");
   while(node != NULL){
      fprintf(output,"%s",node->data); 
      node = node->next; 
  }
}




void Mergesort(struct Nnode **Head, int sort_checker){ //add column parameter to see which sorting algo we need to use

   //basic algo for Mergesort
   //base case
   
   int check = sort_checker;
   struct Nnode *head = *Head; 
   
   if(head == NULL || (head->next == NULL)){
      return; 
    }

    struct Nnode* Half1; 
    struct Nnode* Half2; 
    
    
   Split(head,&Half1,&Half2); //splits the LL into two halves
   
    //recursively calls Mergesort until LL is small enough to sort
   Mergesort(&Half1,check); 
    
    Mergesort(&Half2,check); 
    
    //final sort algo
 
    if(sort_checker == 0){
      *Head = SortingStrings(Half1,Half2); 
     }
     else if(sort_checker == 1){
     
       *Head = SortingInts(Half1,Half2); 
      }
      else{
         *Head = SortingDoubles(Half1,Half2); 
      }
 }


