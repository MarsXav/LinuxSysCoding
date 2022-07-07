#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// int pthread_cancel(pthread_t thread);
// 	function: cancel a thread (terminate a thread)
// 		  when a cancellation point is found the thread will be cancelled


void *callback(void *arg){
	printf("child thread: %ld\n", pthread_self());
	for (int i = 0; i < 5; i++) { printf("c: %d ", i);sleep(1);}
	printf("\n");
	return NULL;
}

int main(){

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, callback, NULL);
	
	// output main tid and child tid
	pthread_cancel(tid);

	for (int i = 0; i < 5; i++){
		printf("%d", i);
	}
	printf("\n");

	printf("tid : %ld, main thread id %ld\n", tid, pthread_self());

	pthread_exit(NULL);
	return 0;
}
