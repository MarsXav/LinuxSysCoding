#include <stdio.h>
#include <wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * This demo is to achieve IPC with the example of "history | grep xxx"
 *
 * The child process is history, after child process ends, data is transferred to parent process
 *
 * function used:
 * 	pipe(): create a annonymous pipe;
 * 	execlp: execute a executable file inside a process
 * 	dup2: relocate the file descriptor from oldfd to newfd
 *
 * */

int main(){
	// create a pipe
	int fd[2];
	int ret = pipe(fd);

	if (ret == -1){
		perror("pipe");
		exit(0);
	}

	// create child process;
	pid_t pid = fork();

	if (pid > 0){
		// parent process
		// read from pipe read end
		char buf[1024] = {0};
		int len = -1;	
		while((len = read(fd[0], buf, sizeof(buf)-1)) > 0){// "-1" is reserved for the terminator
			//print filtered data
			printf("%s", buf);
			memset(buf, 0, 1024);
		}
		wait(NULL);
	} else if (pid == 0){
		// child process
		// relocate fild descriptor stdout_fileno -> fd[1]
		dup2(fd[1],STDOUT_FILENO);
		// execute history
		execlp("history","history",NULL);
		perror("execlp");
		exit(0);
	} else {
		perror("fork");
		exit(0);
	}

	return 0;
}
