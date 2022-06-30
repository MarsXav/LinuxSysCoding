// achieve file copy with mmap
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){
	// mmap the original file
	int fd = open("test.txt", O_RDWR);
	//get file size of the original file
	int len = lseek(fd, 0, SEEK_END);
	// create a new file (expand the file)
	int fd_new = open("new_test.txt", O_RDWR | O_CREAT, 0664);
	truncate("new_test.txt", len); 
	write(fd_new, " ",1);
       	// map the new file to the memory
	void *ptr = mmap(NULL,len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	void *ptr_new = mmap(NULL,len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_new, 0);
	if (ptr == MAP_FAILED || ptr_new == MAP_FAILED) perror("mmap");
	// copy the data from original file to the new file
	memcpy(ptr_new, ptr, len);
	// release resources
	munmap(ptr_new, len);
	munmap(ptr, len);
	close (fd); close(fd_new);

	return 0;
	
}
