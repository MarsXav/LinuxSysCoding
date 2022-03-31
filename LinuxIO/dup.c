#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int main(){
    /*
    * int dup(int oldfd);
    * function: copy the file descriptor
    * returns a new file descriptor
    */
    int fd = open("test.txt", O_RDWR | O_CREAT, 0664);
    int fd1 = dup(fd);

    if (fd1 == -1){
        perror("dup");
        return -1;
    }

    printf("fd: %d, fd1: %d",fd,fd1);
    close(fd);

    /*
     * int dup2(int oldfd, int newfd);
     * function: relocate the file descriptor from oldfd to newfd
     * oldfd must be a valid file descriptor
     */
    int fd2 = dup2(fd,fd1);
    if (fd2 == -1){
        perror("dup2");
        return -1;
    }

    return 0;
}
