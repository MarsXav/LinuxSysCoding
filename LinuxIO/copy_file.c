#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

/* ssize_t read(int fd, void *buf, size_t count);
 * 	fd: file director
 * 	buf: array/array* area where data stores
 * 	count: size of the array
 *	returns bytes read
 * ssize_t writet(int fd, const void *buf, size_t count);
 * 	count: size of data to be input
 * 	returns bytes input
 */
int main(){
	// open test.txt
	
	int srcfd = open("test.txt", O_RDONLY);
	if (srcfd == -1)
		perror("open");
		return -1;
	// create a new file
	int destfd = open("cpy.txt",O_WRONLY | O_CREAT, 0664);
	// read & write
	char buf[1024] = {0};
	int len = 0; 
	while((len = read(srcfd,buf,sizeof(buf)))>0){
		write(destfd,buf,len);
	}
	// close file	
	close(destfd);
	close(srcfd);
}
