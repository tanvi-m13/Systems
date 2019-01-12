/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//DEFINE THE NODES FOR THE LL
typedef struct Nnode
{       
        char *data; 
        char* val_sort;
        struct Nnode* next;
        
} Nnode;




void Split(struct Nnode* Head, struct Nnode **front, struct Nnode **back);
//******************************************************************************************
// This function splits the linked list several times during the merge process.                                                                       
// It is recursively called within the Mergesort() function. 
// This function is called until the split in a mergesort is complete. 
//******************************************************************************************

struct Nnode* SortingInts(struct Nnode *Half1, struct Nnode *Half2);
//******************************************************************************************
// This function sorts the LL based on an integer value of the column given. 
// With this function, the LL is sorted in ascending order after the split has
// been done on the LL. 
//******************************************************************************************

struct Nnode* SortingDoubles (struct Nnode *Half1,struct Nnode *Half2);
//******************************************************************************************
// This function sorts the LL based on a double value of the column given. 
// With this function, the LL is sorted in ascending order after the split has
// been done on the LL. 
//******************************************************************************************

struct Nnode* SortingStrings(struct Nnode *Half1,struct Nnode *Half2);
//******************************************************************************************
// This function sorts the LL based on a string value of the column given. 
// With this function, the LL is sorted in alphabetical ascending order after 
// the split has been done on the LL. 
//******************************************************************************************

void PrintStrings (struct Nnode*node, char* input,char *filename, char *dirOut);
//******************************************************************************************
// This function is used at the end to print the final sorted LL after the 
// mergesort has been completed. The PrintStrings Function traverses the LL 
// until the end and prints each node and line as it goes through.  
//******************************************************************************************

void Mergesort(struct Nnode **Head, int sort_checker);
//*****************************************************************************************
// This is a recursive function that calls all of the other previously stated
// functions of the mergesort.c file until the mergesort is complete. By the 
// end of the function, the LL is completely sorted based on the chosen order. 
//******************************************************************************************


void readDirectory(char *inputDir, char *outputDir, char *sortField, char*srcDir);
//******************************************************************************************
// This method is split into two parts that incorporates fork twice at two different points. 
// It reads directories and what is stored inside them. If it reads a directory, 
// it will recursively call the method until it cannot anymore. In this case, 
// when it finds a CSV, it will call the sorting method and sort it accordingly.  
//*******************************************************************************************



