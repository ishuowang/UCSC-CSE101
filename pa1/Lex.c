#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"List.h"

#define MAX_LEN 100

// For more information $ man strdup
char *strdup(const char *str){
   int n = strlen(str) + 1;
   char *dup = malloc(n);
   if(dup){
      strcpy(dup, str); 
   }
   return dup;
}

int main(int argc, char * argv[]){
   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];

   // Check command line for correct number of arguments
   if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // Open files for reading and writing 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // Count the number of lines in the input file
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL )  {
      line_count++;
   }

   // Read file in to lines
   rewind(in);    // $ man rewind
   char** str_list = (char**) calloc(sizeof(char*), line_count + 1);
   int str_list_idx = 0;
   // Put the string to heap memory using malloc
   while( fgets(line, MAX_LEN, in) != NULL )  {
      str_list[str_list_idx] = strdup(line); 
      str_list_idx++;
   }

   // Insert indics one by one into the List
   // Performe a insertion sort
   List L = newList();
   append(L, 0);
   moveFront(L);
   for(int i = 1; i < line_count; i++){ // insert the ith element
      moveFront(L);
      while(index(L) >= 0){
         if(strcmp(str_list[get(L)], str_list[i]) > 0){
            break;
         }
         moveNext(L);
      }
      if(index(L) < 0){
         append(L, i);
      }else{
         insertBefore(L,i);
      }
   }
 
   // Write the result to out file
   moveFront(L);
   while(index(L) >= 0){
      int x = get(L);
      fprintf(out, "%s", str_list[x]);
      moveNext(L);
   }

   // Free memory
   freeList(&L);  // Actually, it performs free(*(&L));
   // Free memory allocated by strdup
   for(int i = 0; i < line_count + 1; i++){
      free(str_list[i]);
   }
   free(str_list);
   // close files
   fclose(in);
   fclose(out);

   return(0);
}
