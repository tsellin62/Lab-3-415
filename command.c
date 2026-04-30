#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void lfcat()
{
/* High level functionality you need to implement: */

	/* Get the current directory with getcwd() */
	
	/* Open the dir using opendir() */
	
	/* use a while loop to read the dir with readdir()*/
	
		/* You can debug by printing out the filenames here */

		/* Option: use an if statement to skip any names that are not readable files (e.g. ".", "..", "main.c", "lab2.exe", "output.txt" */
			
			/* Open the file */
			
			/* Read in each line using getline() */
				/* Write the line to stdout */
			
			/* write 80 "-" characters to stdout */
			
			/* close the read file and free/null assign your line buffer */
	
	/*close the directory you were reading from using closedir() */
	DIR* ptr;
	struct dirent* read_dir;
	char path[256];
	memset(path, 0, sizeof(path));
	if (getcwd(path, sizeof(path)) == NULL) {
		char msg[] = "Could not print working directory.\n";
		write(STDOUT_FILENO, msg, strlen(msg));
	}
	ptr = opendir(path);

	while ((read_dir = readdir(ptr)) != NULL) {
		if ((read_dir->d_type == DT_REG) && (strcmp(read_dir->d_name, "output.txt") != 0)) {
			char filepath[512];
			snprintf(filepath, sizeof(filepath), "%s/%s", path, read_dir->d_name);

			FILE *fp = fopen(filepath, "r");
			if (fp == NULL) continue;

			char *line = NULL;
			size_t len = 0;
			
			write(STDOUT_FILENO, "File: ", 6);
			write(STDOUT_FILENO, read_dir->d_name, strlen(read_dir->d_name));
			write(STDOUT_FILENO, "\n", 1);

			while (getline(&line, &len, fp) != -1) {
				line[strcspn(line, "\r")] = '\0';
				write(STDOUT_FILENO, line, strlen(line));
				write(STDOUT_FILENO, "\n", 1);
			}

			free(line);
			line = NULL;
			fclose(fp);

			write(STDOUT_FILENO, "\n", 1);
			for (int i = 0; i < 111; i++) {
				write(STDOUT_FILENO, "-", 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
	}	

	write(STDOUT_FILENO, "\n", 1);
	closedir(ptr);
}
