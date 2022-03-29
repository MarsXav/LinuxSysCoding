#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
 * int open(const char *pathname, int flags, mode_t mode);
 * parameters:
 * pathname: path the file is to be created
 * flags: access permission settings
 * 	O_CREAT: create a file if the file doesnt exist
 * 	typeof(flag) is int
 * mode: octnumber, represent the permiission of the new created file
 * 	the final permission if mode&umask
 * 	umask is to eliminate soome permission
 */
int main(){
	int fd = open("create.txt",O_RDWR | O_CREAT, 0777);
	if (fd == -1){
		perror("open");
	}
	close(fd);
	return 0;
}
