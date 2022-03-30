#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


int main(){
    /*
 * int access (const char *pathname, int mode);
 * function: identify if the file has certain access, or if the file exists
 * parameters:
 *      pathname;
 *      mode:
 *          R_OK: read
 *          W_OK: write
 *          X_OK: execute
 *          F_OK: file
 *      return:
 *          0
 */
     int ret = access("test.txt",F_OK);
     if (ret == -1){
         perror("access");
         return -1;
     }
     printf("file found");
 /*
 * int chmod(const char *pathname, mode_mode);
 * function: chmod
 * parameters:
 *      mode:
 *          permission needs to be changed
 *      returns 0 on success
 */
     int mod = chmod("test.txt",0777);
     if (mod == -1){
         perror("chmod");
         return -1;
     }
     printf("permission changed")
     return 0;
/*
 * int truncate(const char *path, off_t length);
 * function: expand/shrink the file to the set size
 * parameters:
 *      -path
 *      -length: the final size of the file
 *      returns 0 on success
 * */

    int tru = truncate("test.txt",200);
    if (tru == -1) {
        perror("truncate");
        return -1;
    }
}
