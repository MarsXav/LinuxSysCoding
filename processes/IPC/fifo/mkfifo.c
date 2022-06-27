#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
/* int mkfifo (const char* parthname, mode_t mode);
 * 	parameters:
 * 	parth_name: pipe name and directory
 * 	mode: permission of the file, same as open and mode
 *
 * 	returns:
 * 	return 0 on success, -1 on failure
 *
 */

int main(){
	int ret = access("fifo",F_OK); //check if the pipe exist
	if (ret == 0) {
		printf("pipe not exist, creating a pipe\n");
		ret = mkfifo("fifo_temp", 0664);

		if (ret == 0){
			perror("mkfifo");
			exit(0);
		}
	} else {
		printf("pipe already exists, no action needed\n");
	}
		
	return 0;
}
