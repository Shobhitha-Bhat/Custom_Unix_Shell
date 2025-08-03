#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "globalUtilities.h"

struct passwd* pw;
char* username;
char hostname[HOST_NAME_MAXLEN];
char* home;
char cwd_path[PATH_MAXLEN];
char prompt_line[PROMPT_LINE_MAXLEN];

void const_user_data(){
    pw=getpwuid(getuid());
    home=pw->pw_dir;
    username = pw->pw_name;
    gethostname(hostname,HOST_NAME_MAXLEN);

}


void initialize_prompt(){  
    getcwd(cwd_path,PATH_MAXLEN);
    if(strncmp(home,cwd_path,strlen(home))==0){
        if(strcmp(home,cwd_path)==0){
            snprintf(prompt_line,PROMPT_LINE_MAXLEN,"~");
        }else{
            snprintf(prompt_line,PROMPT_LINE_MAXLEN,"~%s",cwd_path+strlen(home));
        }
    }else{
        snprintf(prompt_line,PROMPT_LINE_MAXLEN,"%s",cwd_path);
    }

    
}

void display_prompt(){
    printf(BOLD_GREEN "%s@%s" RESET ":" BOLD_BLUE "%s" RESET YELLOW"$ \n" RESET,username,hostname,prompt_line);
}