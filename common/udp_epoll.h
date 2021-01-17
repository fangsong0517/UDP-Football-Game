/*************************************************************************
	> File Name: udp_epoll.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月17日 星期日 21时13分06秒
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

void add_event(int epollfd, int fd, int events);
void del_event(int epollfd, int fd, int events);
int udp_connect(int epollfd, struct sockaddr *serveraddr);
int udp_accept(int epollfd, int fd);
#endif
