#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * pid_t waitpid(pid_t pid, int *wstatus, int options);
 * function: recycle selected child process, set status as block/unblocked
 * parameters:
 * 	pid: pid > 0: any child pid
 * 	     pid == 0: recycle child processes of the current process group
 * 	     pid == -1: recycle all child processes, equivilent to wait() (most commonly used)
 * 	     pid < -1: recycle any process group id
 * 	options: block or nonblock
 * return:
 * 	>0: return pid of child process
 * 	=0: options=WNOHANG, meaning there are child processes exist
 * 	-1: error or no child processes
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
        if (pid > 0){//parent process
                while(1){
			printf("parent, pid = %d\n",getpid());
			int status;
			sleep(1);
                        int ret = waitpid(-1,&status,WNOHANG);//parent process blocks here;
                        if (ret == -1) break;
			else if (ret == 0) continue;
			else if (ret > 0){
				if(WIFEXITED(status)){
					printf("exit number: %d\n",WEXITSTATUS(status));
				}
				if(WIFSIGNALED(status)){
					printf("signal interupted:%d\n",WTERMSIG(status));
				}

				printf("Child killd, pid = %d\n", ret);
                	}
		}
        }
        else if (pid == 0){//child process
                while(1){
                        printf("child,pid: %d",getpid());
                        sleep(1);
                }
		exit(0);
        }
	return 0;
}

