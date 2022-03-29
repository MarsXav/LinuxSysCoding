// int stat(cons char *pathname, struct stat *statbuf);
// funtion: obtain file information
// params:
// 	-pathname;
// 	-stratbuf: struct variable, save file information
// 	(see <man 2 stat>)
// return 0;
//
// int lstat(const char *pathname, struct stat *statbuf);
// function: obtain the link stat
//

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	struct stat statbuf;
	int ret = stat("test.txt",&statbuf);
	if (ret == -1){
		perror("stat");
		return -1;
	}	
	printf("size: %ld\n",statbuf.st_size);
	return 0;
}
