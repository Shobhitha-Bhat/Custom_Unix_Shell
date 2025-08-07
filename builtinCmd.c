#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "globalUtilities.h"
#include "error.h"

char *OldDir;

void cd(Arglist* arg){
    char *cur_dir = getcwd(NULL,0);
    if(arg->size==2){
        char* newpath=NULL;
        if(strcmp("-",arg->args[1])==0){
            if(OldDir==NULL){
                OldDir=strdup(home);
            }
            newpath=strdup(OldDir);
        }else{
        newpath=malloc(strlen(home)+strlen(arg->args[1])+2);
        snprintf(newpath,"%s%s",home,arg->args[1])
        }
        if(chdir(newpath)<0){
            throw_error();
        }else{
            free(OldDir);
            OldDir=strdup(cur_dir);
        }
        free(newpath);
    }
    else if(arg->size==1){
        if(chdir(home)<0){
            throw_error();
        }else{
            free(OldDir);
            OldDir=strdup(cur_dir);
        }
    }
    else{
        printf("cd : Too many arguments\n");
    }
    free(cur_dir);
}



void pwd(Arglist* arg){
    char *current_working_dir = getcwd(NULL,0);
    printf("%s",current_working_dir);
    free(current_working_dir);
}

void echo(Arglist* arg){
    for(int i=1;i<arg->size;i++){
        printf("%s",arg->args[i]);
    }
    printf("\n");
}
