#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

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
                if (pid == 0){
                break;
                }
        }
        if (pid > 0){//parent process
                while(1){
			sleep(1);
                        printf("parent, pid: %d", getpid());
			int status;
                        int ret = waitpid(-1,&status,WNOHANG);//parent process blocks here;
                        if (ret == -1) break;
			if (ret == 0) continue;
			else if (ret > 0){
				if(WIFEXITED(status)){
					printf("exit number: %d\n",WEXITSTATUS(st));
				}
				if(WIFSIGNALED(st)){
					printf("signal interupted:%d\n",WTERMSIG(st));
				}

				printf("Child killd, pid = %d\n", ret);
                	}
		}
        }
        else if (pid == 0){//child process
                while(1){
                        prinf("child,pid: %d",getpid());
                        sleep(1);
                }
        }
	return 0;
}

