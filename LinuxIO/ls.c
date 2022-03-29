// simulate ls-l command
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //identify if the parameters are correct
    if (argc < 2) {
        printf("%s filename\n", argv[0]);
        return -1;
    }
    // obtain file info with stat
    struct stat st;
    int ret = stat(argv[1], &st);
    if (ret == -1) {
        perror("stat");
        return -1;
    }
    // obtain file type and permission
    char perms[11] = {0};
    switch (st.st_mode & S_IFMT) {
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFREG:
            perms[0] = 'r';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        case S_IFSOCK:
            perms[0] = 's';
            break;
        default:
            perms[0] = '?';
            break;
    }
    //ownership of the file
    perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';

    //group
    perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';

    //others
    perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

    //hard connections
    int linkNum = st.st_nlink;

    //file owner
    char *fileUser = getpwuid(st.st_uid) -> pw_name;

    //file group
    char *fileGroup = getgrgid(st.st_gid) -> gr_name;

    //file size
    long int fileSize = st.st_size;

    //modified time
    char *time = ctime(&st.st_mtime);
    char mtime[512] = {0};
    strncpy(mtime,time, strlen(time) -1);
    //
    char buf[1024];

    sprintf(buf,"%s %d %s %ld %s %s", perms, linkNum, fileUser, fileSize, mtime, argv[1]);
    printf("%s\n",buf);
}
