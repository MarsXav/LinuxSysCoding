#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
// int kill (pid_t pid, int sig)
// 	function: send sig to pid
// 	parameters:
// 		pid:
// 			pid > 0 : signal sent to designated process
// 			pid = 0 : signal sent to process group
// 			pid = -1 : signal sent to processes which have limites of receiving the signal
// 			pid < -1: sig is sent to every process in the process group whose ID is -pid	
// 		sig: macro of signal
//
// int raise(int sig)
// 	function: send signal to the current process
// 	parameters:
// 		sig: signal to be sent
// 	return: 
// 		0 on success
// 		non 0 on fail
//
// void abort(void)
// 	function: send SIGABRT to the process, kill the process
//

int main(){
	pid_t pid = fork();
	if (pid == 0){
		int i = 0; 
		for (i = 0; i < 5; i++){
		printf("child process\n");
		sleep(1);
		}
	} else {
		printf("parent process\n");
		sleep(2);
		printf("kill child process...");
		int ret = kill(pid, SIGINT);
	}
	return 0;
}
