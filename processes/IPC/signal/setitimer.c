#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value)
//
// 	function: set timer, precision: ms, set timer in cycles
// 	parameters: which: ITIMER_REAL: counts down in real time: when timer goes up, SIGALRM is sent to the process
// 			   ITIMER_VIRTUAL: user-mode CPU time consumed by the process, when timer goes up, SIGVTALRM is sent to the process
// 			   ITIMER_PROF: both user + system time consumed by the process, when timer goes up, SIGPROF is sent to the process
// 		    new_value: set the attribute of the alarm
// 		    	       
// 		    	       struct itimerval { timer structure
//					struct timeval it_interval // the time interval
//					struct timeval it_value // delay how many seconds to execute timer
// 		    	       };
// 		    	       struct timeval {
//					time_t  tv_sec; //seconds
//					suseconds_t tv_usec //micro seconds
// 		    	       };
// 		    old_value: record last timer parameter, normally not used
//	return: on success return 0, -1 on fail

int main(){
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
