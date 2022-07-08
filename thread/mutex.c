// thread sychronisation: when there is one thread is working, other threads cannot operate on the memory address until it finished working
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *attr);
// 	function: initialise mutex
// 	parameters:
// 		*restrict: the pointer with *restricted cannot be operated by another pointer
//
// int pthread_mutex_destroy(pthread_mutex_t *mutext);
// 	function: release mutex resources
//
// int pthread_mutex_lock(pthread_mutex_t *mtex);
// 	function, blocked
//
// int pthread_mutex_trylock(pthread_mutex_t *mutex);
// 	function: try to lock, if lock fails, return
//
// int pthread_mutex_unlock(pthread_Mutex_t *mutex);

int no = 100;

//create a mutex
pthread_mutex_t mutex;

void *sellticket(void *arg){


	//set tickets
	while(1){	
		//add mutex
		pthread_mutex_lock(&mutex);
		if (no > 0){
			usleep(5000);
			printf("thread: %ld, no. %d\n",pthread_self(), no);
			no--;
		} else {	
		//unlock mutex
			pthread_mutex_unlock(&mutex);
			break;
		}

		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(){
	// initialise mutex
	pthread_mutex_init(&mutex, NULL);

	//create 3 child threads
	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, sellticket, NULL);
	pthread_create(&tid2, NULL, sellticket, NULL);
	pthread_create(&tid3, NULL, sellticket, NULL);

	//set thread detach to recycle the resourses
	pthread_detach(tid1);
	pthread_detach(tid2);
	pthread_detach(tid3);

	pthread_exit(NULL); // exit main thread

	//release mutex resources
	pthread_mutex_destroy(&mutex);

	return 0;
}
