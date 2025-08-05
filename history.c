#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "globalUtilities.h"
#include "history.h"

// FILE *fp;
char ch;



void add_to_history(char* input){
fp=fopen("history_file.txt","a");
fwrite(input,1,strlen(input),fp);
fwrite("\n", 1, 1, fp);
fclose(fp);
}


char* get_prev_cmd(long* file_pointer_index){
    char* line=malloc(1024);
    if (!line) return NULL;
    fp=fopen("history_file.txt","r");

    // fseek(fp,0,SEEK_END);
    long file_position =*file_pointer_index;
    if (file_position == 0) {
        fclose(fp);
        free(line);
        return NULL;
    }
    // do{
    //     fseek(fp,--pos,SEEK_SET);
    //     fread(&ch,1,1,fp);
    // }while(ch=='\n' && file_position>0);

    //move back to find the first \n
    while(file_position>0){
        fseek(fp,--file_position,SEEK_SET);
        fread(&ch,1,1,fp);
        if(ch=='\n'){
            break;
        }
    }

//from that point move to back again to find \n
    while(file_position>0){
        fseek(fp,--file_position,SEEK_SET);
        fread(&ch,1,1,fp);
        if(ch=='\n'){
            file_position++;
            break;
        }
    }
    //after finding the newline we did file_position++ but fp didnt get upadted..so we do it here
    fseek(fp,file_position,SEEK_SET);

    //get the entire line from the current file_position
    if(fgets(line, 1024, fp)){
        if(strlen(line)>0 && line[strlen(line)-1]=='\n'){
                line[strlen(line)-1]='\0';
            }
            *file_pointer_index=file_position;
            fclose(fp);
            return line;

    }

 free(line);
    fclose(fp);
    return NULL;

}


char* get_next_cmd(long* file_pointer_index){
    char* line=malloc(1024);
    fp=fopen("history_file.txt","r");
    long file_position =*file_pointer_index;
    fseek(fp,0,SEEK_END);
    long endOfFile=ftell(fp);
    if(file_position>=0 && file_position<endOfFile){
        fseek(fp,file_position,SEEK_SET);
        if(fgets(line, 1024, fp)){

            if(strlen(line)>0 && line[strlen(line)-1]=='\n'){
                line[strlen(line)-1]='\0';
            }
            *file_pointer_index=ftell(fp);
            fclose(fp);
            return line;
        }
        free(line);
    }
fclose(fp);
    return NULL;

}


