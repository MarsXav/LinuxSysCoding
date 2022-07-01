#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
// determine how many numbers can computer count in 1 second;
//
// The actual time consumed = kernal time + user time + time IO consumed
// IO consumes time pretty badly
//
// Clock is irrelevant to the process state, no matter what state does the process has, the alarm counts down


int main(){
	int count = 0;
	int time = alarm(1);
	while(1){
		count++;
		printf("%d\n", count);
	}
	return 0;
}
