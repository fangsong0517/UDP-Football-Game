/*************************************************************************
	> File Name: client_recver.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月27日 星期三 17时21分58秒
 ************************************************************************/

#include "head.h"
#include "common.h"

extern int sockfd;

void *client_recv(void *arg) {
    while(1) {
        struct FootBallMsg msg;
        bzero(&msg, sizeof(msg));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        if(msg.type & FT_TEST) {
            DBG(RED"HeartBeat from Server 心\n"NONE);
            msg.type = FT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if(msg.type & (FT_MSG | FT_WALL)) {
            DBG(GREEN"Server Msg : "NONE"%s\n", msg.msg);
        } else if(msg.type & FT_FIN){
            DBG(GREEN"Server is going to stop.\n"NONE);
            endwin();
            exit(0);
        } else {
            DBG(GREEN"Msg Unsupport\n"NONE);
            exit(0);
        }
        
    }
}

