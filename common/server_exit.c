/*************************************************************************
	> File Name: server_exit.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月27日 星期三 18时14分42秒
 ************************************************************************/

#include "head.h"
#define MAX 50
extern struct User *rteam, *bteam;

void server_exit(int signum) {
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    for(int i = 0; i < MAX; i++) {
        if(rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        if(bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
    }
    endwin();
    DBG(RED"Server stopped!\n"NONE);
    exit(0);
}
