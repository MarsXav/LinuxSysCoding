#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
// read write lock is more effective because when reading, the threads won't be blocked, only when writing will block
// create 8 threads, 3 write, 5 read

int i = 1;
pthread_rwlock_t rwlock;

void *Write(void *arg){
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		i++;
		printf("write, tid: %ld, num: %d\n", pthread_self(), i);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
	return NULL;
}
void *Read(void *arg){
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		printf("reading, tid: %ld, num: %d\n", pthread_self(), i);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
	return NULL;
}
int main(){
	//create rwlock
	pthread_rwlock_init(&rwlock, NULL);

	//create threads
	pthread_t wtids[3], rtids[5];
	for (int i = 0;  i < 3; i++){
		pthread_create(&wtids[i], NULL, Write, NULL);
	}
	for (int i = 0; i < 5; i++){
		pthread_create(&rtids[i], NULL, Read, NULL);
	}

	//detach
	for (int i = 0; i < 3; i++){
		pthread_detach(wtids[i]);
	}
	for (int i = 0; i < 5; i++){
		pthread_detach(rtids[i]);
	}
	pthread_exit(NULL);

	return 0;
}
