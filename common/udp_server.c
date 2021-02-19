/*************************************************************************
	> File Name: udp_server.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 15时19分42秒
 ************************************************************************/

#include "head.h"
#include "color.h"
int socket_create_udp(int port) {
    int server_listen;
    if ((server_listen = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    make_nonblock(server_listen);
    if (bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return server_listen;
}


