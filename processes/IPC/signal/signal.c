#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// typedef void (*sighandler_t) (int);
// sighandler_t signal (int signum, sighandler_t handler);
// 	function: set capture action of a signal
// 	parameter:
// 		signum: signal to capture
// 		handler: how to handle the signal:
// 			SIG_IGN: ignore the signal
// 			SIG_DFL: default action
// 			call back function: kernal evokes, how to handle the signal
// 				needs programmer prepare according to the actual needs
// 				function pointer is the approach of callback
// 	return: returns the previous value of the signal handler on success, NULL on first evoke, on fail return SIG_ERR
//
// 	SIGKILL / SIGSTOP cannot be captured

void myAlarm(int num){
	printf("Singal captured, signal num is :%d\n", num);
}
int main(){
	// register signal capture
	__sighandler_t  ret = signal(SIGALRM, myAlarm);
	// after 3 seconds, set timer for every 2 seconds 
	struct itimerval new_value;
	// set the value
	
	new_value.it_interval.tv_sec = 2;// time interval
	new_value.it_interval.tv_usec = 0;
	
	new_value.it_value.tv_sec = 3;//delay
	new_value.it_value.tv_usec = 0;

	int time = setitimer(ITIMER_REAL, &new_value, NULL);//unblocked
	printf("timer starts\n");
	getchar();

	return 0;

}
