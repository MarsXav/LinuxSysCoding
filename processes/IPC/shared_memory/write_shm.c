#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <stdio.h>

int main(){
	//create a shhared memory
	int shmid = shmget(100, 4096, IPC_CREAT | 0664);
	
	//link with current process
	void *ptr = shmat(shmid, NULL, 0);

	//write data
	char * str = "hello";
	memcpy(ptr, str, strlen(str)+1);

	printf("print any key to coninue");
	getchar();
	
	//unlink connection
	shmdt(ptr);
	
	//delete shared memory
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
