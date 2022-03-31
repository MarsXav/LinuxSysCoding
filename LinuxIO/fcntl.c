#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* int fcntl(int fd, int cmd, ... arg );
 * fd: file descriptor
 * cmd: how to operate the fd
 *      FD_DUPFD: duplicate fd
 *          int ret = fcntl(fd,F_DUPFD)
 *      F_GETFL: get file flag
 *      F_SETFL: set file flag
 *          must contain: O_RDONLY, O_WRONLY, O_RDWR
 *          optional: O_APPEND, O_ASYNC, NONBLOK: reflects the call action of the function
 *
 */
int main(){
    //duplicate file descriptor
    int fd = open("test.txt",O_RDWR);
    int ret = fcntl(fd,F_DUPFD);
    if (ret == -1){
        perror("fcntl");
        return -1;
    }

    //obtain and modify the file status
    int flag = fcntl(fd,F_GETFL);
    flag |= O_APPEND;
    int ret1 = fcntl(fd,F_SETFL,flag);
    if (ret1 == -1){
        perror("fcntl");
        return -1;
    }
    char *str = "HELLO";
    write(fd,str,strlen(str));
    close(fd);
}
