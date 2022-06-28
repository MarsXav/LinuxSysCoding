// Achieve chat function with fifo
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){

	// identify if the pipe exist
 	int ret = access("fifo2", F_OK);
	if (ret == -1){
		printf("pipe2 does not exist, creating pipe");
		ret = mkfifo("fifo2", 0664);
		if (ret == -1) perror("mkfifo");
	}	

	ret = access("fifo2", F_OK);
	if (ret == -1){
		printf("pipe1 does not exist, creating pipe");
		ret = mkfifo("fifo2", 0664);
		if (ret == -1) perror("mkfifo");
	}

	// open fifo1 with rdonly
	int fd2 = open("fifo1", O_RDONLY);
       	if (fd2 == -1) perror("open"); 
	printf("pipe fifo1 succesfully opened, waiting to read..."); 
	int fd1 = open("fifo2", O_WRONLY);
	if (fd1 == -1) perror("open");
	printf("pipe fifo2 succesfully opened, waiting to write...");

	// write data
	char buf[1024];
	while(1) {

		//read data
		memset(buf, 0, 128);
		ret = read(fd2, buf, 128);
		if (ret <= 0){
			perror("read");
			break;
		}
		printf("buf: %s\n", buf);
	
		// obtain data
		memset(buf, 0, 128);
		fgets(buf, 128, stdin);
		// write data
		ret = write(fd1, buf, strlen(buf));
		if (ret == -1) perror("write");
	}

	//close fd;
	close(fd1);close(fd2);



	return 0;
}
