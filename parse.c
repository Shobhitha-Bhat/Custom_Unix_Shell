#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "history.h"
#include "input.h"
#include "globalUtilities.h"

void parse(){
    enable_raw_input();
    while(1){
        char *user_input = get_input();
        add_to_history(user_input);      
        tokenize_into_args(user_input); 
        display_prompt();
        free(user_input)
    }
    
}