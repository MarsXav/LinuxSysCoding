//write data to the fifo
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
	// identify if the file exists
	int ret = access("test", F_OK);
	if (ret == -1){
		printf("pipe not exist, creating pipe\n");
	// create pipe file
		ret = mkfifo("test", 0664);
	}
	// open pipe
	int fd = open("test", O_WRONLY);//write only
	if (fd == -1) perror("open");
	for (int i = 0; i < 100; i++){
		char buf[1024];
		sprintf(buf, "hello, %d\n", i);
		printf("writing data: %s\n", buf);
		int len = write(fd, buf, strlen(buf));
		sleep(1);
	}
	close(fd);
	return 0;
}
