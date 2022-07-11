#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// producer - consumer model


// int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
// int pthread_cond_cond_destroy(pthread_cond_t *cond);
// int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
// 	function: blocked satate, envoking will block the thread
// int pthread_cond_timewait(pthread_cond_t *restrict cond, pthread_mutex_t* restrict mutex, 
// 	wait for how long
// int ptrhead_cond_broadcast(pthread_cond_t *cond);
// int pthread_cond_signal(pthread_cond_t *cond);
// 	wake all waiting threads	


//mutex
pthread_mutex_t mutex;

//conditional variable
pthread_cond_t cond;
struct Node{
	int data;
	struct Node* next;
};

struct Node* head;

void *produce(void* arg){
	//create new nodes and append to the list
	while(1){
		pthread_mutex_lock(&mutex);
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode -> next = head;
		head = newNode;
		newNode -> data = rand() % 1000;
		printf("add node, val : %d, tid: %ld\n", newNode -> data, pthread_self());
		pthread_cond_signal(&cond);

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return NULL;
}
void *consume(void* arg){
	while(1){
		pthread_mutex_lock(&mutex);
		struct Node *temp = head;
		if(head) {
			head = head -> next;
			printf("delete node: val: %d, tid: %ld\n", temp -> data, pthread_self());
			free(temp);
			pthread_mutex_unlock(&mutex);
			sleep(1);
		} else {
			pthread_cond_wait(&cond, &mutex);
			//when pthread_cond_wait is envoked, mutex will be unlocked
			pthread_mutex_unlock(&mutex);
		} 
	}
	
	return NULL;
}


int main(){
	//create 5 producer and 5 consumer threads
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_t ptids[5], ctids[5];
	for (int i = 0; i < 5; i++){
		pthread_create(&ptids[i], NULL, produce, NULL);
		pthread_create(&ctids[i], NULL, consume, NULL);
	}

	for (int i = 0; i < 5; i++){
		pthread_detach(ptids[i]);
		pthread_detach(ctids[i]);
	}

	while(1){
		sleep(10);
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_exit(NULL);

	return 0;
}
