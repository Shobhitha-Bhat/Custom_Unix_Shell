#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>


#include "args.h"
#include "error.h"



void execute(Arglist* args){
    execute_command(args);
}

void execute_command(Arglist* args){
    if(args->args==0)return;
    if(strcmp(args->args[0],"cd")==0){
        cd(args);
    }
    else if(strcmp(args->args[0],"echo")==0){
        echo(args);
    }
    else if(strcmp(args->args[0],"pwd")==0){
        pwd(args);
    }
    else if(strcmp(args->args[0]."ls")==0){
        ls(args);
    }
    else{
        execute_external_binary(args);
    }
}

void execute_external_binary(Arglist* args){
    pid_t pid=fork();
    int status;
    if(pid==0){
        //child process to execute binaries using execvp
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);

        execvp(args->args[0],args->args);
        exit(EXIT_FAILURE);      //incase if exec fails
    }else{
            setpgid(pid, 0);
            // signal(SIGTTOU, SIG_IGN);   //ignore backgroud processes to write to terminal
            tcsetpgrp(0, pid);          //set terminals' control tothe new child process
            waitpid(pid, &status, WUNTRACED);    //wait till childreturns
            tcsetpgrp(0, getpgrp());            //take control back from the child to parent
    }

}