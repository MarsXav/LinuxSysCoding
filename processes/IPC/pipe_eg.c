//realise the pipe function in terminal
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int fd[2];
	int ret = pipe(fd);
	pid_t pid = fork();

	if (pid > 0){
	//parent process
	//read from child process
	char buf[1024] = {0};
	int len = -1;
	while(len = read(fd[0],buf, sizeof(buf - 1)) > 0){
		printf ("%s",buf);
		memset(buf,0,1024);
		wait(NULL);
	}
	} else if (pid == 0){
	//child process
	close(fd[0]);
	//reallocate file descriptor
	dup2(fd[1], STDOUT_FILENO);
	//execute ps aux
	execlp("ps","ps","aux",NULL);
	perror("execlp");
	exit(0);
	}
}
