//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//
// compile:
//
//     gcc -std=c17 -Wall -o FileIO FileIO.c
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file, then count and print tokens
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;

      // get tokens in this line
      token_count = 0;
      tokenBuffer[0] = '\0';

      // get first token
      token = strtok(line, " \n");
      
      while( token!=NULL ){ // we have a token
         // update token buffer
         strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;

         // get next token
         token = strtok(NULL, " \n");
      }

      // print tokens in this line
      fprintf(out, "line %d contains %d ", line_count, token_count);
      fprintf(out, "token%s: \n", token_count==1?"":"s" );
      fprintf(out, "%s\n", tokenBuffer);
   }

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}
