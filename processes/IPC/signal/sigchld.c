// Conditions of SIGCHLD generate:
// 	1. WHen child process ends,
// 	2. when child process receives SIGSTOP signal and stops
// 	3. when child process is at halt state but receives SIGCONT
// Capture of SIGCHLD can effectively eliminate problems like zombie process

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void func(int num){
	printf("signal captured: %d\n", num);
	// recycle PCB resources
	while(1){
		int ret = waitpid(-1, NULL, WNOHANG);
		if (ret > 0){
			printf("child die, pid = %d\n", ret);
		} else if (ret == 0){
			break;
		} else if (ret == -1){
			break;	
		}
	}
}

int main(){
	//set block signal set, to avoid when child process ends, parent process hasn't finished signal capture registration
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);

	//create some child processes
	pid_t pid;
	for (int i = 0; i < 20; i++){
		pid = fork();
		if (pid == 0) break;
	}

	if (pid > 0){
		//capture SIGCHLD when child process dies
		struct sigaction act;
		act.sa_flags = 0;
		act.sa_handler = func;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD, &act, NULL);

		//after registration, unblock
		sigprocmask(SIG_UNBLOCK, &set, NULL);

		while(1){
			printf("parent process pid is: %d\n", getpid());
			sleep(1);
		}
	} else {
		printf("child process pid is: %d\n", getpid());
	}

	return 0;
}
