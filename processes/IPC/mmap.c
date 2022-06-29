// realise IPC with mmap
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
// 	function: map a file or equipment's data to memory
// 	parameters:
// 		void *addr: NULL, assigned by kernel
// 		size_t length:  lenghth of data to be mapped, cannot be 0, better to be set as the length of the file: stat/lseek
// 		int prot: memory protection of the mapping: PROT_READ, PROT_WRITE, PROT_NONE, PROT_EXEC;
// 			To operate on mapped memory, read access must be granted
// 		int flags: determines whether updates to the mapping are visible to other processes mapping the same region and whether updates are carried through to the underlying file
// 			MAP_SHARED: mapping data updates with disk data
// 			MAP_PRIVATE: out-synced, mapped data updates, disk data doesn not update, new file will be created
// 		int fd: file descriptor to be mapped
// 			get thru open()
// 			file size must be greater than 0, open operation limites must not conflict with prot
// 		off_t offset: 0: no offset
// 	return:
// 		on success, returns a pointer to the mapped area
//
// int munmap(void *addr, size_t length)
// 	function: release mmap
// 	parameter:
// 		addr: pointer to the mem to be released
// 		length: mem size to be released, same as the parameter in mmap

//Related IPC with mmap:
//	Create memory mapping area
//	Create child process
//	Both processes share mem mapping area
//Unrelated IPC with mmap:
//	Create a disk file with size != 0
//	Process1: create memory mapping area thru the disk file
//		Obtain a pointer to operate the memory
//	Process2: create memory mapping area thru the disk file
//		Obtain a pointer to operate the memory
//	Communicate with memory mapping area

int main(){
	// open a file
	int fd = open("test.txt", O_RDWR);
	int size = lseek(fd, 0, SEEK_END);// obtain the size of the file
	// create memory area
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED) perror("mmap");
	//create child process
	pid_t pid = fork();
	if (pid > 0){
		//parent
		wait(NULL);
		char buf[64];
		strcpy(buf, (char*)ptr);
		printf("read data: %s\n", buf);		
	
	} else {
		//child
		strcpy((char*) ptr, "Hello parent process");
	}
	//close memory mapping area
	munmap(ptr, size);
	return 0;
}
