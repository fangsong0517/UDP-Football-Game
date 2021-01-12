/*************************************************************************
	> File Name: server.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 18时38分15秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/color.h"
#include "../common/udp_server.h"
#include "../common/common.h"
#include "../common/game.h"


struct User *rteam;
struct User *bteam;

char *conf = "./server.conf";

int main(int argc, char **argv) {
    int opt, port = 0, listener;
    pthread_t draw_t;
    while((opt = getopt(argc, argv, "p:")) != -1) {
        switch(opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);

    if(argc > 1) {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
        exit(1);
    }


    if(!port) port = atoi(get_value(conf, "PORT"));

    court.width = atoi(get_value(conf, "COLS"));
    court.height = atoi(get_value(conf, "LINES"));
    court.start.x = 3;
    court.start.y = 1;

    if((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    DBG(GREEN"INFO"NONE " : Server start on Port %d\n", port);

    pthread_create(&draw_t, NULL, draw, NULL);


    while(1) {
        w_gotoxy_puts(Message, 1, 1, "test");
        struct LogRequest lg;
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        recvfrom(listener, (void *)&lg, sizeof(lg), 0, (struct sockaddr *)&client, &len);
        char info[1024];
        sprintf(info, "Login : %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        w_gotoxy_puts(Message, 1, 2, info);
    }

    return 0;
}
