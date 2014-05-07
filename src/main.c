/*============================================================================
 *  @file:      main.c
 *  @author:    Bambridge E. Peterson
 *  @date:      April 8th, 2014
 *===========================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"
#include "sml.h"



int main(int argc, char *argv[]) {

    Command_Args cargs;
    memset(&cargs, 0, sizeof(Command_Args));

    ParseArgs(argc, argv, &cargs);
    // used to store values from memory in order to perform
    // various aritmetic operations on it
    int accumulator = 0;

    // hold the next instruction to be executed
    int instructionCounter = 0;

    // current instruction
    int instructionRegister = 0;
    
    // the operation given in the instruction
    int operationCode = 0;

    // the operand given in the instruction
    int operand = 0 ;

    // this represents the operation either given by the user
    // or read from a preloaded file
    int instruction;

    int j;



    // init our memory 
    int memory[MEM_SIZE];
    for (j = 0; j <= MEM_SIZE - 1; j++) {
        memory[j] = 0;
    }

    printInstructions(1);

    j = 0;

    do {

      if (j < 10) {
        printf("0%d ? ", j); 
      }
      else {
        printf("%d ? ", j);
      }

      scanf("%d", &instruction);
     
      if (instruction >= -9999 && instruction <= 9999) {
        memory[j] = instruction;
      }

      j += 1;
     
    } while (instruction >= -9999 && instruction <= 9999);

     printf("\n*** Program loading completed ***\n");
     printf("*** Program execution begins ***\n\n");
     dump(accumulator, operationCode, operand, instructionCounter, instructionRegister, memory);
     printf("\n\n");

    do {
      instructionRegister = memory[ instructionCounter ];

      operationCode = instructionRegister / MEM_SIZE;

      operand = instructionRegister % MEM_SIZE;
      
      instructionCounter += 1; 

      switch (operationCode ) {

        case ADD: 

          accumulator += memory[ operand ];
          break;

         case SUBTRACT:

           accumulator -= memory[ operand ];
           break;

         case MULTIPLY:

           accumulator *= memory[ operand ];
           break;

         case DIVIDE:

           accumulator /= memory[ operand ];
           break;

         case READ:
          
           printf("Enter data for location %d ? ", instructionCounter);
           scanf( "%d", &memory[ operand ] );	  
           break;

         case WRITE:

           printf("output: %i\n", memory[ operand ] );
           break;

         case LOAD:
       
           accumulator = memory[ operand ];
           break;

         case STORE:

           memory[ operand ] = accumulator;
           break;	

         case BRANCH:
               
           instructionCounter = operand;
           break;

         case BRANCHNEG:
            if( accumulator < 0) {
                instructionCounter = operand;
            }
            break;

         case BRANCHZERO:

            if( accumulator == 0 ) {
                  instructionCounter = operand;
            }
            break;

         case HALT:

            printf("\n***Simpletron execution has completed***\n");
            dump(accumulator, operationCode, operand, instructionCounter, instructionRegister, memory);
            break;
        } // end of switch

    } while(operationCode != 43);

    printf("\n");

    return 0;


} // end of main

void dump(int accumulator, int operationCode, int operand, 
    int instructionCounter, int instructionRegister, int *m) {
    
    int k;

    printf(" accumulator: %d\n instructionCounter:%d\n instructionRegister: %d\n operationCode: %d\n operand: %d\n",        
            accumulator, instructionCounter, instructionRegister, operationCode, operand);

    printf("\nMemory:\n");
  
    for(k = 0; k < 10; k++) {
       if(k == 0) {
         printf("  ");
       }
       printf("%6d", k);
    }
    
    for(k = 0; k < MEM_SIZE; k++) {
        if( ( k % 10 ) == 0 ) {
          printf("\n");
          printf("%2d", k);
        }
   
        printf(" %5i", m[k]);
    } 

} // end of dump


void printInstructions(version) {

    if (version == 1) {
    printf("\n\n");
    printf("***  Welcome to the Simpletron!  ***\n");
    printf("***  Please enter your program one instruction  ***\n");
    printf("***  (or data word) at a time. The location  ***\n");
    printf("***  in memory one along with a question mark  ***\n");
    printf("***  You then type the word for that location.  ***\n");
    printf("***  Type the sentinel -99999 to stop entering your program  ***\n\n");
    } else {
        // TODO: write new instructoins. We want to give
        // the user an opportunity to enter a file containing
        // SimpleTron Machine language
    }
}  // end of printInstructions

void Usage() {
    printf("usage: <main.c> -f <filename.sml> \n");
    exit(1);
}

/**
 * @name:   ParseArgs
 * @param:
 * @param:
 * @param
 *
 *
 */
void ParseArgs(int argc, char * argv[], args_p cap) {
    int c;

    while ( (c = getopt(argc, argv, "f:")) != -1) {
        switch(c) {
            case 'f':

                // TODO: what should we do in this case? It means a file can
                // be passed to the command line which contains a SML
                // program
                cap->filename = optarg;
                printf("filename: %s\n", cap->filename);
                break;
            default:
                Usage();
        }

    }
}
 
