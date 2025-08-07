#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "globalUtilities.h"

FILE *fp;
void clean_up(){
    fclose(fp);
}

void finish(){
    
}