#include <unistd.h>

/* l(list) v(vector) p(path) e(environment)
 *
 * int execl(const char* path, const char *arg, ...);
 * function:
 * 	execute a executable file inside a process
 *
 * parameters: 
 * 	path: path or name of the file needs to be executed 
 * 	arg: 
 * 		first argument is the name of the file to be executed
 * 		second and following: list of parameters
 * 		arguments need to be ended with a NULL
 *
 * return:
 * 	only on fail returns -1
*/
/*
 * int execlp(const char *file, const char *arg){
 *	function: search for the executable file in the environement
 *	parameters: 
 *		file: file name of the executable file name
 * }
 */
int main(){
	// create a child process execl
	pid_t pid = fork();
	if(pid > 0){
		printf("pid:%d\n",getpid());

	} else if(pid == 0){
		execl("test","test",NULL);
		printf("pid:%d\n",getpid());
	}
}
