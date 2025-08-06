#ifndef ARGS_H
#define ARGS_H

#define INIT_ARG_SIZE 2

typedef struct Arglist{
    char** args;
    int no_of_args;
}Arglist;


void tokenize_into_args(char* );
void init_args_struct();

#endif