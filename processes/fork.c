#include <sys/types.h>
#include <unistd.h?
#include <stdio.h>

/*
 * pid_t fork(void);
 * function: create child process
 * return: PID o the child process will be returned in mother process, child process returns 0. returns -1 in mother process on fail.
 *
 */

int main() {
    //create a child process
    pid_t pid = fork();

    //determine it's mother process or child process
    if (pid > 0) {
        //if greater than 0, child PID is returned
        printf("pid: %d\n", pid);
        printf("ppid: %d, pid: %d\n", getppid(), getpid());
    } else if (pid == 0) {
        //child process returned
        printf("pid:%d, ppid:%d\n", getpid(), getppid());
    }
}