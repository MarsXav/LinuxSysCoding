#include <stdio.h>
#include <string.h>
#include <pthread.h>

// int pthread_detach(pthread_t thread);
// 	fucntion: detach a thread. When a detached thread is detached, the resources of the thread is released to system.
// 		  cannot detach multiple times, cannot detach a joined thread
// 	return 0 on success, error number on fail

void *callback(void *arg){
	printf("child thread: %ld\n", pthread_self());
	return NULL;
}

int main(){

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, callback, NULL);
	
	// output main tid and child tid
	printf("tid : %ld, main thread id %ld\n", tid, pthread_self());

	ret = pthread_detach(tid);

	//after detaching join the child thread
	
	ret = pthread_join(tid, NULL);
	if (ret) {
		char *str = strerror(ret);
		printf("error: %s\n", str);
	}

	pthread_exit(NULL);
	return 0;
}
