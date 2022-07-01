#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// unsigned int alarm(unsigned int seconds);
// 	function: set a timer when envolked, SIGALRM is sent to the process when timer is up
// 	parameter: timer set (unit: seconds), 0 when the alarm is invalid
// 	return: if no timer was set, return 0, if another timer was set, the remaining time of the alarm was set
//
// SIGALRM: on default terminate the process, each process has and only has an unique timer

int main(){
	int time = alarm(5);
	printf("seconds = %d\n", time);
	sleep(2);
	time = alarm(10);
	printf("seconds = %d\n", time);
	while(1){
		sleep(1);
		printf("prgram running\n");
	}
	return 0;
}

