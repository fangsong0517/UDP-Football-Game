/*************************************************************************
	> File Name: common.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 15时34分30秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
char *get_val(char *path, char *key);
void make_nonblock_ioctl(int fd);
void make_block_ioctl(int fd);
void make_nonblock(int fd);
void make_block(int fd);
#endif
