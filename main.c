#include <stdio.h>
#include <stdlib.h>
#include "string_parser.h"
#include "command.h"
#include "string.h"
#include <unistd.h>

int running = 1;

//enum to help choose command
typedef enum {
	LFCAT,
	QUIT,
	UNKNOWN
} command_type;

//get command
command_type get_command(char* str) {
	if (strcmp(str, "lfcat") == 0) return LFCAT;
	if (strcmp(str, "quit") == 0) return QUIT;
	return UNKNOWN;
}

//trim leading and trailing whitespace
char* trim(char* str) {
	while (*str == ' ' || *str == '\n' || *str == '\r') {
		str++;
	}
	char* end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n' || *end == '\r')) {
		*end = '\0';
		end--;
	}
	return str;
}

//same as str_tokenize but for splitting with a space
command_line space_split(char* str) {
	command_line cmd;
	int count = 0;
	char** lst = (char**)malloc(sizeof(char*));
	char* token = strtok(str, " ");
	while (token != NULL) {
		lst = realloc(lst, (count + 1) * sizeof(char*));
		lst[count] = strdup(token);
		count++;
		token = strtok(NULL, " ");
	}
	cmd.num_token = count;
	cmd.command_list = lst;
	return cmd;
}

int execute_command(command_line* args) {
	switch (get_command(args->command_list[0])) {
		case LFCAT:
			if (args->num_token == 1) {
				lfcat();
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: lfcat\n");
				return 1;
			}
			break;
		case QUIT:
			if (args->num_token == 1) {
				running = 0;
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: quit\n");
				return 1;
			}
			break;
		case UNKNOWN:
			printf("Error! Unrecognized command: %s\n", args->command_list[0]);
			return 1;
			break;
	}
	return 1;
}	

int main(int argc, char* argv[]) {
	char *input_line = NULL;
	size_t len = 0;
	ssize_t read;

	if (argc < 2) {
		printf("Usage: ./lab3 input.txt\n");
		return 1;
	}
	
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Error opening input file\n");
		return 1;
	}

	freopen("output.txt", "w", stdout);

	while (running) {
		read = getline(&input_line, &len, input);
		if (read != -1) {
			command_line cmd = str_tokenize(input_line);
			for (int i = 0; i < cmd.num_token; i++) {
				command_line args = space_split(trim(cmd.command_list[i]));
				if (args.num_token > 0) {
					if(execute_command(&args)) {
						free_command_line(&args);
						break;
					}
				}	
				free_command_line(&args);
			}		
			free_command_line(&cmd);	
		}
		else {
			break;
		}
		free(input_line);
		input_line = NULL;
		len = 0;
	}

	free(input_line);
	fclose(input);
	return 0;
}
