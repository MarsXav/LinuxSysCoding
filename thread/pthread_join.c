#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// int pthread_join(pthread_t thread, void **retval);
// 	function: connect with terminated thread (recycle child thread's resources)
// 		The function is blocked function, only one thread can be envoked upon one call
// 	Parameters: thread: tid
// 		    retval: reveive return value of exit of child thread: a second order pointer to obtain the value of the return of callback function
// 		     	return: 0 upon success, error no upon fail
//

int val = 10;

void *callback(void *arg){
	printf("child thread id: %ld\n", pthread_self());
	sleep(3);
	pthread_exit((void*)&val);
}
int main(){
	//create a child process
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, callback, NULL);
	if (ret){
		char * errstr = strerror(ret);
	}
	//in main thread:
	printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());

	//main thread calls pthread_join to recycle child thread resources
	int *thread_retval;
	ret = pthread_join(tid, (void**) &thread_retval);

	printf("exit data :%d\n", *thread_retval);

	// as long as the child thread is running, the following message won't be printed
	printf("recycle success\n");

	// exit main thread, this action won't affect other working threads
	pthread_exit(NULL);

	printf("main thread exits\n");//this wont execute

	return 0;
}
