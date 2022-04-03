#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/*
 * void exit(int status;)
 *
 * void _exit(int status);
 *
 * status parameter: status information when process exits, when parent process recycles child status
 *
 * when envoke, the process will envoke the exit function then refresh the I/O cache and closes the file descriptor then envoke _exit() system function to abord the process
 */
int main(){
	printf("test\n");
	
	exit(0);

	return 0;
}
