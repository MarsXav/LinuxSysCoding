#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//int open(const char *pathname, int flags); //open an existing file
/*
 * pathname: file path
 * flags: access permission settings and more
 * 	O_RDONOLY, O_WRONLY, O_RDWR the settings are mutually exclusive
 * returns a new file descriptor
 * errno: Linux funtion lib, global variable, records the latest error number;
 */

// void perror(const char *s)
/* function: print error infor conrresponds to errno
 * 
 */

//int open(const char *pathname, int flags, mode_t mode); //create a new file
int main(){
	int fd = open("a.txt",O_RDONLY);
	if (fd == -1){
		perror("open");
	}
	// File operations
	close(fd);
	return 0;
}
