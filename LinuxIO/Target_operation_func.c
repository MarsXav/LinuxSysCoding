#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
/*
* int mkdir(const char *pathname, mode_t mode)
 * parameters:
 *      mode: permission (mode & umask)
* */
    int mkd = mkdir("test",0777);
    if (mkd == -1){
        perror("-1");
        return -1;
    }
/*
 * int rename();
 * */
    int rn = rename("test","TEST");
    if (rn == -1){
        perror("rename");
        return -1;
    }
/*
 * int chdir(const char *path)
 * function: change the working directory of the process
 * parameters:
 *      path: directory needs to be changed
 *
 * char *getcwd(char *buf, size_t size);
 * function: get the current directory
 * parameters:
 *      -buf: saving directory, pointing to an array
 *      -size: size of the array
 * returns a pointer to the memory
 * */
    char buf[128];
    getcwd(buf,sizeof(buf));
    printf("current directory is: %s", buf);

    int chd = chdir("~/Desktop/LinuxSysCoding");
    if (chd == -1){
        perror("chdir");
        return -1;
    }
    return 0;

}
