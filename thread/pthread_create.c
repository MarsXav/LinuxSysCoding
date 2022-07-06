#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
//	function: create a child thread
//	parameters:
//		thread: output parameter, child thread ID will be written to the variable
//		attr: attribute, NULL
//		start_routine: logic that child thread needs to be processed
//		arg: pass parameter to start_routine
//	return: 0 on success, error no on fail

void *callback(void *arg){
	printf("child thread\n");
	printf("arg value: %d\n", *(int*)arg);
	return NULL;
}

int main(){
	//create a child thread
	pthread_t tid;
	int num = 10;
	int ret = pthread_create(&tid, NULL, callback, (void*)&num);
	if (ret){
		//get error number
		char *errstr = strerror(ret);
		printf("error: %s\n", errstr);
	} 
	sleep(1);
	return 0;
}
