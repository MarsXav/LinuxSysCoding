// create a daemon process, each 2s time is copied and write to a disk file
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

void work(int num){
	//after captruing signal, obtain sys time, write into disk file
	time_t tm = time(NULL);
	// convert time format
	struct tm * loc = localtime(&tm);
	char *str = asctime(loc);
	int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
	write (fd, str, strlen(str));
	close(fd);
}

int main(){
	//1. create a child process
	pid_t pid = fork();

	if (pid > 0) exit(0);

	//2. create a new session with child process
	setsid();

	//3. set mask
	umask(022);

	//4. change working directory
	chdir("~/Desktop/LinuxSysCoding/processes/Daemon_proc");

	//5. close/relocate file directory;
	int fd = open("/dev/null", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	//6. custom logic
	// capture signal
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = work;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);

	//create timer
	struct itimerval val;
	val.it_value.tv_sec = 2;
	val.it_value.tv_usec = 0;
	val.it_interval.tv_sec = 2;
	val.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &val, NULL);

	while(1) sleep(10);
	return 0;
}
