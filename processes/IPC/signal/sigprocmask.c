#include <signal.h>
#include <unistd.h>
#include <stdio.h>

//int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
//	function: fetch and/or change the signal mask to the kernel
//	parameters:
//		    SIG_BLOCK : add user set signal set to kernel, the initial data in kernel remain unchanged. after setting: mask |= set
//		    SIG_UNBLOCK : unblock the signal set in kernal: mask &= ~set
//		    SIG_SETMASK : replace original values in kernel
//		oldset: the previous saved signal set, normally set as NULL
//	return: 0 on success, -1 on error
//		error no will be returned
//int sigpending(sigset_t *set);
//	function: fecth the unsettled signal set
//	return: 0 on success, -1 on error
int main(){// print all pending signals
	// set #2 #3 signal block
	sigset_t set;
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	//modify signal set in kernel
	sigprocmask(SIG_BLOCK, &set, NULL);
	int num = 0;
	while(1){
		num++;
		sigset_t pendingset;
		sigemptyset(&pendingset);
		sigpending(&pendingset);

		for (int i = 1; i <= 32; i++){
			if (sigismember(&pendingset, i) == 1){
				printf("1");
			} else if (sigismember(&pendingset, i) == 0) {
				printf("0");
			}
		}
		printf("\n");
		sleep(1);
		if (num == 10){
			sigprocmask(SIG_UNBLOCK, &set, NULL);
		}
	}
	return 0;
}		    
