//read data from fifo
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
	// open pipe file
	int fd = open("test", O_RDONLY);
	if (fd == -1) perror("open");
	while(1){
		char buf[1024] = {0};
		int len = read(fd, buf, sizeof(buf));
		if (len == 0){
			printf("NO data to read");
			break;
		}
		printf("receive buf: %s\n", buf);
	}
	close(fd);
	return 0;
}
