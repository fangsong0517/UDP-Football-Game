/*************************************************************************
	> File Name: common.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 15时34分24秒
 ************************************************************************/

#include "head.h"

char *get_value(char *path, char *key) {
    FILE *fp = NULL;
    ssize_t nrd;
    char *line = NULL, *sub = NULL;
    size_t linecap;
    if(path == NULL || key == NULL) {
        fprintf(stderr, "Error in argument!\n");
    }
    if((fp = fopen(path, "r")) == NULL) {
        perror("fopen");
        return NULL;
    }
    while((nrd = getline(&line, &linecap, fp)) != -1) {
        if((sub = strstr(line, key)) == NULL) {
            continue;
        } else {
            if(line[strlen(key)] == '=') {
                strncpy(conf_ans, sub + strlen(key) + 1, nrd - strlen(key) - 2);
                *(conf_ans + nrd - strlen(key) - 2) = '\0';
                break;
            }
        }
    }
    free(line);
    fclose(fp);
    if(sub == NULL) {
        return NULL;
    }
    return conf_ans;
}

void make_nonblock_ioctl(int fd) {
    unsigned long ul = 0;
    ioctl(fd, FIONBIO, &ul);
}

void make_block_ioctl(int fd) {
    unsigned long ul = 1;
    ioctl(fd, FIONBIO, &ul);
}

void make_nonblock(int fd) {
    int flag;
    if((flag = fcntl(fd, F_GETFL)) < 0) {
        return;
    }
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}

void make_block(int fd) {
    int flag;
    if((flag = fcntl(fd, F_GETFL)) < 0) {
        return;
    }
    flag &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}
