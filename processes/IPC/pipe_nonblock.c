#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
/*
 * int pipe (int pipefd[2]);
 * 	function: create a annonymous pipe to communicate between processes
 * 	parameters: int pipefd[2], which serves as a output parameer
 * 		pipefd[0] refers to read end of the pipe
 * 		pipefd[1] refers to write end
 * 	return: on success returns 0, -1 on fail
 * 	ps. annonymous pipe only applies to IPC between communications between processes with relations
 * 	    on default, the pipe is choked, if no data sends, read choked, if pipe is full, write choked.
 */
int main(){
	//create pipe before fork
	int pipefd[2];
	int ret = pipe(pipefd);
	if (ret == -1){
		perror("pipe");
		exit(0);
	}

	//get pipe size
	long size = fpathconf(pipefd[0], _PC_PIPE_BUF);
	printf("Pipe size: %ld\n",size);

	//create child process
	pid_t pid = fork();

	if (pid > 0){
		//parent process
		char buf[1024] = {0};

		int flags = fcntl(pipefd[0], F_GETFL);// obtain origin flag
		flags |= O_NONBLOCK;// modify the flag
		fcntl(pipefd[0], F_SETFL, flags);//set new flag

		while(1){
			//read data from pipe read end
			int rd = read(pipefd[0], buf, sizeof(buf));
			printf("rd = %d\n",rd);
			printf("Parent received: %s, pid: %d\n",buf, getpid());
			memset(buf,0,1024);
			sleep(1);
		}
	}
	else if (pid == 0){
		//child process
		char buf[1024] = {0};
		while(1){
			//write data from pipe write end
			char *str = "child writing";
			write(pipefd[1], str, strlen(str));
			sleep(2);
		}
	}
	return 0;
}

