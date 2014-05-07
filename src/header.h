/*
 * ===========================================================================
 * @name:       header.h
 * @author:     Bambridge E. Peterson
 * @desc    Header file for the SimpleTron projectg
 *
 *
 *============================================================================
 */

/**
 * structs
 */
typedef struct command_line_args_s {
    char * filename;
} Command_Args;

typedef Command_Args * args_p;

/**
 * Function Prototypes
 */

void ParseArgs(int argc, char * argv[], args_p cap);

void Usage();

void printInstructions();

void dump(int accumulator, int operationCode, int operand,
        int instructionCounter, int instructionRegister, int *m);



