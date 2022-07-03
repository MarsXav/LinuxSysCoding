#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
// 	function: check or to change the processing of a signal
// 	parameters: signum: macronum
// 		    act: processing actions after capturing the signal
// 		    	    struct sigaction{
//				void (*sa_handler)(int); // function pointer, points to the process function after capture
//				void (*sa_sigaction)(int, siginfo_t *, void*); 
//				sigset_t sa_mask; // temproraly block the signal set
//				int sa_flags; //how to handle the captured signal
//				void (*sa_restorer)(int);//restored
// 		    	    }
// 	return 0 on success, -1 on fail
void myAlarm(int num){
	printf("Singal captured, signal num is :%d\n", num);
}
int main(){
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = myAlarm;

	sigemptyset(&act.sa_mask); // tempororaly block the signal set

	// register signal capture
	sigaction(SIGALRM, &act, NULL);
	// after 3 seconds, set timer for every 2 seconds 
	struct itimerval new_value;
	// set the value
	
	new_value.it_interval.tv_sec = 2;// time interval
	new_value.it_interval.tv_usec = 0;
	
	new_value.it_value.tv_sec = 3;//delay
	new_value.it_value.tv_usec = 0;

	int time = setitimer(ITIMER_REAL, &new_value, NULL);//unblocked
	printf("timer starts\n");
	while(1);

	return 0;

}
