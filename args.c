#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>


#include "args.h"
#include "error.h"

Arglist* init_and_add_args(char* single_command){
    Arglist* arg=malloc(sizeof(Arglist));
    if(arg==NULL){
        throw_error();
    }
    arg->args= malloc(sizeof(char*)*INIT_ARG_SIZE);
    for(int i=0;i<INIT_ARG_SIZE;i++){
        arg->args[i]=NULL;
    }
    arg->no_of_args=0;

        //get the commands and its arguments one by one using strtok
    char *token = strtok(single_command," \t");
    while(token !=NULL){
        AddCmdArgs(arg,token); //add token to the arg object of type Arglist
        token=strtok(NULL," \t");   //NULL says that continue tokenizing from where it left last time.
    }
    return arg;
}


void AddCmdArgs(Arglist* arg, char* token){
        if(token==NULL){
            arg->args[arg->no_of_args]=NULL;     //it helps to null terminate ur command....like ls -l NULL...tells when that cmd ends.
            arg->no_of_args++;
            return;
        }
        char *newarg=malloc(sizeof(char*)* (strlen(token)+1));
        if(newarg==NULL){
            throw_error();
        }
        strcpy(newarg,token);
        arg->args[arg->no_of_args]=newarg;
        arg->no_of_args++;
}

void FreeArgs(Arglist *arg){
    //free in the reverse order of allocating
    for(int =0;i<arg->size;i++){
        free(arg->args[i]);   //free each command and its arguments
    }
    free(arg->args);   //free the pointer that was pointing to these commands
    free(args);      //free the structure itself...
}

void tokenize_into_args(char* user_input){
    user_input[strcspn(user_input,'\n')]='\0';

    char *store_tokens;
    char *single_command = strtok_r(user_input,";\n",&store_tokens);
    while(token!=NULL){
        Arglist *cmd_and_args = init_and_add_args(single_command);
        execute(cmd_and_args);
        *single_command = strtok_r(user_input,";\n",&store_tokens);
        FreeArgs(cmd_and_args);
    }
    while()
}