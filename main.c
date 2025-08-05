#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "globalUtilities.h"
#include "parse.h"
#include "cleanup.h"

int main(){
    const_user_data();
    while(1){
        initialize_prompt();
        display_prompt();
        parse();
        finish();
    }
    // atexit(clean_up());

}



