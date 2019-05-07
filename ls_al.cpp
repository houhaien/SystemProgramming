/*************************************************************************
	> File Name: ll.cpp
	> Author: houhaien 
	> Mail: github.com/houhaien 
	> Created Time: 2019年05月07日 星期二 15时50分51秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <pwd.h>
using namespace std;
void modeshow(int mode, char str[]) {
   // char str[1024];
    strcpy(str, "----------");
    switch (mode & S_IFMT) {
           case S_IFBLK:  str[0] = 'b';                 break;
           case S_IFCHR:  str[0] = 'c';                 break;
           case S_IFDIR:  str[0] = 'd';                 break;
           case S_IFIFO:  str[0] = 'p';                 break;
           case S_IFLNK:  str[0] = 'l';                 break;
           case S_IFREG:  str[0] = '-';                 break;
           case S_IFSOCK: str[0] = 's';                 break;
           default:       str[0] = '?';                 break;
           }

    if ((mode & S_IRUSR)) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';

}

void showinfo(char *name, int bj) {
    struct stat ss;
    if (stat(name, &ss) < 0) {
        perror("stat");
        return ;
    }
    struct passwd *uid, *grp;
    //struct group *grp;
    uid = getpwuid(ss.st_uid);
    grp = getpwuid(ss.st_gid);
    char modep[20];
    modeshow(ss.st_mode, modep);
	if(bj == 1) {
    	//printf("%s\n", name);
    	printf("%10s", modep);
    	printf("%10ld", (long) ss.st_nlink);
    	printf("%10s", uid->pw_name);
    	printf("%10s", grp->pw_name);
    	printf("%15d", ss.st_size);
    	printf("%20.16s", ctime(&ss.st_mtime));
        printf("\t");
    	printf("%s\n", name);
	} else {
			if(name[0] != '.')
    		printf("%s\t", name); 
    }
}
void ls_l(char *argv, int bj) {
    DIR *dir;
    struct stat ss ;
    struct dirent *read;
    stat(argv, &ss);
    int isd = 0;
    if(S_ISDIR(ss.st_mode)) {
        isd = 1;
    }
    if(isd) {
        chdir(argv);
        if((dir = opendir(argv)) == NULL) {
            perror("opendir");
            exit(1);
        }
        while ((read = readdir(dir)) != NULL) {
            showinfo(read->d_name,bj);
        }
        if(bj == 0) printf("\n");
        chdir("..");
        closedir(dir);
    } else {
        showinfo(argv,bj);
        printf("\n");
        }
    
}
int main(int argc, char *argv[]) {
	int bj = 0;
    if (argc == 1){
        char *str;
        strcpy(str, ".");
        ls_l(str, bj);
    } else if (argc == 2 && strcmp(argv[1], "-al") == 0) {
        char str[50];
        bj = 1;
        strcpy(str, ".");
        ls_l(str,bj);
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (i == 1 && strcmp(argv[i], "-al") == 0 ){
                bj = 1;
                continue;
			}
            ls_l(argv[i], bj);
        }
    }
    return 0;
}

