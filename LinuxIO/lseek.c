#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/* off_t lseet(int fd, off_t offset, int whence);
 * whence:
 * 	SEEK_SET: set the offset of the file pointer
 * 	Seek_CUR: set the offset: current positionn + the second param offset
 * 	SEEK_END: set the offset: file size + second param offset
 * function:
 * 	1 move the file pointer to the file head
 * 		lseek(fd,0,SEEK_SET);
 * 	2 Obtain the current file pointer
 * 		lseek(fd,0,SEEK_CUR);
 * 	3 Obtain file length
 * 		lseek(fd,0,SEEK_END);
 * 	4 extend file length
 * 		lseed(fd,<bytes extended>,SEEK_END)
 *
 */
int main(){
	int fd = open("test.txt", O_RDWR);
	if (fd == -1){
		perror("open");
	}
	// extend file length
	int ret = lseek(fd,100,SEEK_END);
	if (ret == -1)
		perror("lseek");
		return -1;
	// write void data
	write(fd," ",1);
	// close file
	close(fd);
	return 0;
}
