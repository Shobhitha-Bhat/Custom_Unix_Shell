#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include"globalUtilities.h"

void throw_error(){
    printf(RED);
    perror("Vsh");
    printf(RESET);
    exit(1);
}