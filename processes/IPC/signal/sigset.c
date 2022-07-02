// The following functions are to handle self created signal set
//
// int sigemptyset(sigset_t *set);
// 	function: empty the data in the signal set, set 0 to all positions in signal set
// 	parameters: signal set needs to be empty
// 	return: 0 on success, -1 on fail
//
// int sigfillset(sigset_t *set);
// 	function: set all position in the set to 1
// 	return: 0 on success, -1 on fail
//
// int sigaddset(sigset_t *set, int signum);
//	function: set the sellected signal position to 1 to block the signal
//	parameter: signum, signal to be blocked
//
// int sigdelset(sigset_t *set, int signum);
// 	function: reverse to sigaddset
//
// int sigismember(const sigset_t *set, int signum)
// 	function: identify if a signal is blocked
// 	return: 1 if signum is blocked, 0 is not blocked, -1 on fail
#include <signal.h>
#include <stdio.h>

int main(){
	//create a signal set
	sigset_t set;
	// clear the signal set
	int ret = sigemptyset(&set);
	// identify if SIGINT is in the set
	ret = sigismember(&set, SIGINT);
	if (ret == 1) printf("SIGINT blocked\n");
	else if (ret == 0) printf("SIGINT not blocked\n");
	//add some signals in set
	ret = sigaddset(&set, SIGINT);
	ret = sigaddset(&set, SIGQUIT);
	ret = sigismember(&set, SIGINT);
	if (ret == 1) printf("SIGINT blocked\n");
	else if (ret == 0) printf("SIGINT not blocked\n");

	//delete some signals in set
	ret = sigdelset(&set, SIGINT);
	ret = sigismember(&set, SIGINT);
	if (ret == 0) printf("SIGINT not blocked\n");
	else if (ret == 1) printf("SIGINT blocked\n");

}
