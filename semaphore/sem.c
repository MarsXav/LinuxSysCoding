//int sem_init(sem_t *sem, int pshared, unsigned int value);
//	functino: initialisation semaphore
//	parameters: sem, adrress pointed
//		    pshared: 0 used inbetween thread, non 0 used others
//		    value: value in semaphore 
//
//int sem_destroy(sem_t *sem);
//	funcion: relese resources
//
//int sem_wait(sem_t *sem);
//	function: semaphore - 1, if value > 0, the decrement proceeds and the fucntion returns
//int sem_trywait(sem_t *sem);
//
//int sem_timedwait(sem_t *sem, const struct timespex *abs_timeout);
//
//int sem_post(sem_t *sem);
//	function: sempathore + 1
//
//int sem_getvalue(sem_t *sem, int *sval);

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
// producer - consumer model

//create two semaphores
sem_t psem, csem;

struct Node{
	int data;
	struct Node* next;
};

struct Node* head;

void *produce(void* arg){
	//create new nodes and append to the list
	while(1){
		sem_wait(&psem);
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode -> next = head;
		head = newNode;
		newNode -> data = rand() % 1000;
		printf("add node, val : %d, tid: %ld\n", newNode -> data, pthread_self());
		sem_post(&csem);
		sleep(1);
	}
	return NULL;
}
void *consume(void* arg){
	while(1){
		sem_wait(&csem);
		struct Node *temp = head;
		head = head -> next;
		printf("delete node: val: %d, tid: %ld\n", temp -> data, pthread_self());
		free(temp);
		sem_post(&psem);
		sleep(1);
		  
	}
	
	return NULL;
}


int main(){
	sem_init(&psem, 0, 8);
	sem_init(&csem, 0, 0);

	//create 5 producer and 5 consumer threads

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

	pthread_exit(NULL);

	return 0;
}
