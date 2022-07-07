#include <stdio.h>
#include <string.h>
#include <pthread.h>

// int pthread_attr_init(pthread_attr_t *attr);
// 	initialise attribute resourses
// int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
// 	get detach state of the thread
// int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
// 	Set thread attribute state

void *callback(void *arg){
	printf("child thread: %ld\n", pthread_self());
	return NULL;
}

int main(){

	// create and initialise a thread variable
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	// set attribute;
	int ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (ret) {
		char *str = strerror(ret);
		printf("error: %s\n", str);
	}
	

	//create a thread
	pthread_t tid;
	ret = pthread_create(&tid, &attr, callback, NULL);

	if (ret) {
		char *str = strerror(ret);
		printf("error: %s\n", str);
	}
	
	// get stack size
	size_t size;
	ret = pthread_attr_getstacksize(&attr, &size);
	printf("The size of the stack is :%ld\n", size);

	// output main tid and child tid
	printf("tid : %ld, main thread id %ld\n", tid, pthread_self());

	ret = pthread_detach(tid);

	//after detaching join the child thread
	
	ret = pthread_join(tid, NULL);
	if (ret) {
		char *str = strerror(ret);
		printf("error using pthread_join: %s\n", str);
	}

	//release attribute resources
	pthread_attr_destroy(&attr);

	pthread_exit(NULL);
	return 0;
}
