/**
 *
 * UNIX pipe program where the parent writes a string to a 1st  pipe.
 * The child process reads this string, reverses the case of each 
 * character, and writes its result back to a 2nd pipe.
 * The parent process then reads this reversed result from the 2nd pipe.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int first_pipe[2];
	int second_pipe[2];
	int i;

	if (pipe(first_pipe) == -1) {
		fprintf(stderr,"First Pipe failed");
		return 1;
	}

 	if (pipe(second_pipe) == -1) {
                fprintf(stderr,"Second Pipe failed");
                return 1;
        }


	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused ends of each pipe */
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);

		/* write to the pipe */
		write(first_pipe[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* now close the write end of the pipe */
		close(first_pipe[WRITE_END]);

		/* read the result from the second pipe */
		read(second_pipe[READ_END], read_msg, BUFFER_SIZE);
		printf("parent read >%s<\n",read_msg);

		close(second_pipe[READ_END]);
	}
	else { /* child process */
		/* close the unused ends of the pipes */
		close(first_pipe[WRITE_END]);
		close(second_pipe[READ_END]);

		/* read from the pipe */
		read(first_pipe[READ_END], read_msg, BUFFER_SIZE);
		printf("child read >%s<\n",read_msg);

		/* reverse the string */
		for (i = 0; i < strlen(read_msg); i++) {
			if (isupper(read_msg[i]))
				write_msg[i] = tolower(read_msg[i]);
			else if (islower(read_msg[i]))
				write_msg[i] = toupper(read_msg[i]);
			else
				write_msg[i] = read_msg[i];
		}

		/* write to the pipe */
		write(second_pipe[WRITE_END], write_msg, strlen(write_msg)+1);
		

		/* close the write end of the pipe */
		close(first_pipe[READ_END]);
		close(second_pipe[WRITE_END]);
	}

	return 0;
}
