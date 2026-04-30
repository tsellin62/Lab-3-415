#include <string.h>
#include <stdlib.h>
#include "string_parser.h"

/*
 
typedef struct
{
    char** command_list;     Array of individual commands separated by ';' 
    int num_token;           Number of tokens/commands found 
} command_line;
 */

command_line str_tokenize(char* str) {
	command_line cmd;
	int count = 0;
	char** lst = (char**)malloc(sizeof(char*));
	char* token = strtok(str, ";");
	while (token != NULL) {
		lst = realloc(lst, (count + 1) * sizeof(char*));
		char* tok_cpy = strdup(token);
		lst[count] = tok_cpy;
		count++;
		token = strtok(NULL, ";");
	}
	cmd.num_token = count;
	cmd.command_list = lst;
	return cmd;
}



/* Function to free the dynamic memory allocated within the command_line struct */
void free_command_line(command_line* control) {
	for (int i = 0; i < control->num_token; i++) {
		free(control->command_list[i]);
	}
	free(control->command_list);
	control->command_list = NULL;
	control->num_token = 0;
}
