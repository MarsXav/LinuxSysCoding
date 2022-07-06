#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// void pthread_exit(void *retval);
// 	function: terminate a thread which is called the function
// 	parameter:
// 		retval: a pointer as a return value, which can be acquired from pthread_join()
//
//int pthread_equal(pthread_t t1, pthread_t t2);
//	function: compare if two threads are same
//	

void *callback(void *arg){
	printf("child thread id: %ld\n", pthread_self());
	return NULL;// this is equivilant to pthread_exit(NULL)
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

	// exit main thread, this action won't affect other working threads
	pthread_exit(NULL);

	printf("main thread exits\n");//this wont execute

	return 0;
}
