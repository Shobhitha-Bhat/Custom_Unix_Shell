#ifndef ARGS_H
#define ARGS_H

#define INIT_ARG_SIZE 2

typedef struct Arglist{
    char** args;
    int no_of_args;
}Arglist;


void tokenize_into_args(char* );
void FreeArgs(Arglist*);
void AddCmdArgs(Arglist* , char* );
Arglist* init_and_add_args(char* );

#endif