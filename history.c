#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

#include "globalUtilities.h"

FILE *fp;

void add_to_history();
void remove_from_history();
void get_prev_cmd();
void get_next_cmd();