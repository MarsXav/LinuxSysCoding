#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/* pid_t wait(int * wstatus);
 * function: 
 * 	wait for any child process to finish, if any child process ends, then the function would recycle the resources of the process:
 * parameters: int *wstatus
 * 	the status when process exits
 * returns:
 * 	on success returns pid of the terminated child process
 * 	on fail returns -1 when all child processes terminates or call fails
 * when call, the process will be blocked until a child process exit or recieved a signal
 */
int main(){
	// create 5 child processes;
	pid_t pid;
	for (int i = 0; i < 5; i++){
		pid = fork();
		if (pid == 0){
		break;
		}
	}
	if (pid > 0){
		while(1){
			printf("parent, pid: %d", getpid());

			int ret = wait(NULL);//parent process blocks here;
			if (ret == -1) break;
			printf("Child killd, pid = %d\n", ret);

			sleep(1);
		}
	}
	else if (pid == 0){
		while(1){
			printf("child, pid: %d\n",getpid());
			sleep(1);
		}
	}
	return 0;
}
