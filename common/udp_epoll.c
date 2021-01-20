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


extern int port;

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
    if((sockfd = socket_create_udp(port)) < 0) {
        perror("socket_udp");
        return -1;
    }
    if(connect(sockfd, (struct sockaddr *)serveraddr, sizeof(struct sockaddr)) < 0) {
        perror("connect");
        return -1;
    }
    DBG(GREEN"INFO"NONE" : After connect.\n fd = [%d]", sockfd);
    send(sockfd, "Login!", sizeof("Login"), 0);
    add_event(epollfd, sockfd, EPOLLIN);
    return sockfd;
}

int udp_accept(int epollfd, int fd) {
    struct sockaddr_in client;
    int new_fd, ret;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));
    socklen_t len = sizeof(struct sockaddr_in);
/*第一条消息是否成功*/
    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    DBG(PINK"RECV"NONE" : %s\n", request.msg);

    if(ret != sizeof(request)) {
        response.type = 1;/*出问题*/
        strcpy(response.msg, "Login failed.");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    response.type = 0;
    strcpy(response.msg, "Login success .Enjoy yourself.\n");
    sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);

    if(request.team) {
        DBG(GREEN"INFO"NONE " : "BLUE" %s on %s : %d login! (%s)\n"NONE, request.name,inet_ntoa(client.sin_addr), ntohs(client.sin_port), response.msg);
        
    } else {
        DBG(GREEN"INFO"NONE " : "RED" %s on %s : %d login! (%s)\n"NONE, request.name,inet_ntoa(client.sin_addr), ntohs(client.sin_port), response.msg);
    } 

    new_fd = udp_connect(epollfd, &client);
    return new_fd;
}
