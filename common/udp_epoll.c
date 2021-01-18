/*************************************************************************
	> File Name: udp_epoll.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月17日 星期日 20时55分18秒
 ************************************************************************/

#include "./color.h"
#include "./common.h"
#include "./udp_client.h"
#include "./udp_server.h"
#include "./head.h"

void add_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void del_event(int epollfd, int fd, int events) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}


int udp_connect(int epollfd, struct sockaddr_in * serveraddr) {
    int sockfd;
    if((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        return -1;
    }
    if(connect(sockfd, (struct sockaddr *)serveraddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return -1;
    }
    add_event(epollfd, sockfd, EPOLLIN);
    return sockfd;
}

int udp_accept(int epollfd, int fd) {
    struct sockaddr_in client;
    int new_fd, ret;
    char msg[512] = {0};
    socklen_t len = sizeof(struct sockaddr_in);
    ret = recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr *)&client, &len);
    if(ret < 0) {
        return -1;
    }

    DBG(GREEN"INFO"NONE " : %s : %d login!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    

    DBG(PINK"RECV"NONE" : %s \n", msg);
    new_fd = udp_connect(epollfd, &client);
    return new_fd;
}
