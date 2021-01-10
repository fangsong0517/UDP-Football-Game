/*************************************************************************
	> File Name: udp_client.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 13时40分34秒
 ************************************************************************/

#include "head.h"
int socket_udp() {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("socket creat.\n");
    return sockfd;
}
