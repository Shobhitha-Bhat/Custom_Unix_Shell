#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include<termio.h>

#include "input.h"
#include "history.h"


struct termios orig_termios;

void disable_raw_input() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_input() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);  // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


char* get_input(){
    char* inp=malloc(sizeof(char)*INPUT_MAXLEN);
    int inp_pointer=0;
    int cursor_pointer=0;
    char c;

    while(read(STDIN_FILENO,&c,1)==1){

        if(c=='\033'){
            char buf[2];
            read(STDIN_FILENO,&buf[0],1);
            read(STDIN_FILENO,&buf[1],1);
            if(buf[0]=='['){
                switch(buf[1]){

                    case 'A': 
                    //up arrow
                    {
                        char* prev=get_prev_cmd();
                        if(prev){
                            int len=strlen(inp);
                            for(int i=0;i<len;i++){
                                printf("\b \b");
                            }
                            strcpy(inp,prev);
                            inp_pointer=strlen(inp);
                            cursor_pointer=inp_pointer;
                            printf("%s",inp);
                        }
                        break;
                    }

                    case 'B':
                    //down arrow
                    {
                        char* next = get_next_cmd();
                        if(next){
                            int len=strlen(inp);
                            for(int i=0;i<len;i++){
                                printf("\b \b");
                            }
                        }
                        strcpy(inp,next);
                        inp_pointer=strlen(inp);
                        cursor_pointer=inp_pointer;
                        printf("%s",inp);
                        break;
                    }

                    case 'C':
                    //move cursor front/right
                    if(cursor_pointer<inp_pointer){
                        printf("\033[C");
                    }
                    break;
                    case 'D':
                    //move cursor back/left
                    if(cursor_pointer>0){
                        printf("\033[D");
                    }
                    break;
                }
            }
        }
        else if(c==127 || c==8 ||c=='\b'){   //backspace
            if(cursor_pointer>0){
                cursor_pointer--;
                inp_pointer--;
                for(int i=cursor_pointer;i<inp_pointer;i++){
                    inp[i]=inp[i+1];
                    // printf("%c",inp[i]);
                }
                printf("\b");   //move one step back
                printf("%s ", &inp[cursor_pointer]);  // reprint the rest and erase last char
                printf("\b"); // move back from the space
                inp[inp_pointer]='\0';

                int len = strlen(&inp[cursor_pointer]);
                for (int i = 0; i < len + 1; i++) {
                    printf("\b");
                }
            }
        }
        else if(c==9){
            //tab
            if(inp_pointer==0)continue;
            else if(inp_pointer>0){
                
            }

        }
        
        
        else if(c>=32 && c<=127){
            for (int i = inp_pointer; i > cursor_pointer; i--) {
                inp[i] = inp[i - 1];
            }
            inp[cursor_pointer]=c;
            cursor_pointer++;
            inp_pointer++;
            printf("%s", &inp[cursor_pointer - 1]);
            int len = strlen(&inp[cursor_pointer]);
            for (int i = 0; i < len; i++) {
                printf("\b");
            }
            
        }
        else if(c=='\n'){
            inp[inp_pointer]='\0';
                return inp;
        }
    }
    
}