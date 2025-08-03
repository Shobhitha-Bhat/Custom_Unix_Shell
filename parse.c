#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "history.h"

void parse(){
    enable_raw_input();
    char *user_input = get_input();

    //add only valid commands from user input to the history file
    add_to_history();



}