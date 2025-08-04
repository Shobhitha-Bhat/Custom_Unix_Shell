#ifndef GLOBALS_H
#define GLOBALS_H

#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

#define HOST_NAME_MAXLEN 128
#define PATH_MAXLEN 128
#define PROMPT_LINE_MAXLEN 128

extern struct passwd* pw;
extern char* username;
extern char hostname[HOST_NAME_MAXLEN];
extern char *home;
extern char cwd_path[PATH_MAXLEN];
extern char prompt_line[PROMPT_LINE_MAXLEN];

extern FILE *fp;
extern long* file_ponter_index;

void const_user_data();
void initialize_prompt();
void display_prompt();
#endif