/*************************************************************************
	> File Name: send_ctl.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年02月19日 星期五 11时11分44秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern struct FootBallMsg ctl_msg;

void send_ctl() {
    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry) {
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0 );
    }
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}

