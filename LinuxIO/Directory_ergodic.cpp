#include <sys/stat.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

/*
 * // open a directory
 * DIR *opendir(const char *name);
 * returns a pointer to the directory stream, which can be reckoned as directory steam
 *
 * // read data in directory
 * struct dirent *readdir(DIR *dirp);
 * returns struct dirent, representing the directory info
 *
 * int closedir(DIR *dirp);
 * */
int getFileNum(const char *path){
    // 1. open directory
    DIR *dir = opendir(path);
    if (dir == nullptr){
        perror("opendir");
        return -1;
    }
    struct dirent *ptr;
    int num = 0;//record file numbers
    while((ptr = readdir(dir)) != nullptr){
        // obtain directory name
        char *dname = ptr -> d_name;
        // omit . and ..
        if (strcmp(dname,".") == 0 || strcmp(dname,"..")==0){
            continue;
        }
        // identify file and directory
        if (ptr -> d_type == DT_DIR){
            // directory, continue scanning
            char newpath[256];
            sprintf(newpath,"%s/%s",path,dname);
            num += getFileNum(newpath);
        }
        if (ptr -> d_type == DT_REG){
           num++;
        }
    }
    return num;
}

int main(int argc, char* argv[]){
    //read number of files in directory
    if (argc < 2){
        cout << argv[0] << endl;
        return -1;
    }
    int ret = getFileNum(argv[1]);
    cout << ret << endl;

    return 0;
}
