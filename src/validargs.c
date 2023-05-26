#include <stdlib.h>

#include "fliki.h"
#include "global.h"
#include "debug.h"

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the various options that were specified will be
 * encoded in the global variable 'global_options', where it will be
 * accessible elsewhere in the program.  For details of the required
 * encoding, see the assignment handout.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * @modifies global variable "global_options" to contain an encoded representation
 * of the selected program options.
 * @modifies global variable "diff_filename" to point to the name of the file
 * containing the diffs to be used.
 */
int compareChar(char* c1, char* c2) {
    while(*c1 && (*c1 == *c2)) {
        c1++;
        c2++;   
    }

    if(*c1 == '\0' && *c2 == '\0')
        return 1;

    return -1;
}

int validargs(int argc, char **argv) {
    // printf("%d\n", argc);
    // fflush(stdout);
    if(argc < 2) {
        return -1;
    }

    // char *pointer = argv;
    // while(pointer != NULL && *pointer != '\0') {
    //     printf("%s", *pointer);
    //     pointer++;
    // }
    int nFlag = 0;
    int qFlag = 0;
    int diffFile = 0;
    global_options = 0;
    char **ptr = argv;
    ptr++;

    // check for  -h flag
    // if -h is first flag found
        // printf("%s\n", *ptr);
        if(compareChar(*ptr, "-h") == 1) {
            // printf("Found -h flag\n");
            global_options = HELP_OPTION;
            return 0;      // ignore any flags after
        }


    while (*(ptr + 1) != NULL) {
        // printf("IN WHILE LOOP\n");
        // fflush(stdout);

        // -n flag
        if(compareChar(*ptr, "-n") == 1) {
            nFlag++;
        }

        // -q flag
        else if(compareChar(*ptr, "-q") == 1) {
            qFlag++; 
        }

       else {
        // printf("STRING %s\n", *(ptr + 1));
        return -1;
       }

        ptr++;
    }


    // printf("VALID ARGS: OUT OF WHILE LOOP\n");
    // fflush(stdout);

    // Check for duplicates
    // if(nFlag > 1 || qFlag > 1) {
    //     printf("CHECKING FOR DUPLICATES\n");
    //     fflush(stdout);
    //     return -1;
    // }

    // Filename DIFF_FILE must be the last argument
    // check if first chracter is -
    // printf("%s\n", *ptr);
    // fflush(stdout);
    char *temp = *ptr;
    if(*temp == '-') {
        // last string is a flag not diff file
        return -1;
        }
    diff_filename = *ptr;

    // Set global_options
    if(nFlag >= 1)  {
        global_options =  NO_PATCH_OPTION;
    }

    if(qFlag >= 1) {
        global_options =  QUIET_OPTION;
    }

    if(nFlag >= 1 && qFlag >= 1) {
        global_options = NO_PATCH_OPTION + QUIET_OPTION;
    }


    return 0;
    //abort();
}
