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

    if((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    DBG(GREEN"INFO"NONE " : Server start on Port %d\n", port);

    pthread_create(&draw_t, NULL, draw, NULL);


    while(1) {
        //
    }

    return 0;
}
