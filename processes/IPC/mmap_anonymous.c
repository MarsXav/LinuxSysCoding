// anonymous map: no need an actual file to acheive mapping

#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

// void *

int main(){

	//create anoymous memory mapping area
	int len = 4096;
	void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED){
		perror("mmap");
	}
	// IPC between processes
	pid_t pid = fork();
	if (pid > 0){
		// parent process
		strcpy((char*) ptr, "hello");
		wait(NULL);
	} else {
	// child process
		sleep(1);
		printf("%s\n", (char*)ptr);
	}
	//relase mapping area
	munmap(ptr, len);
	return 0;
}
