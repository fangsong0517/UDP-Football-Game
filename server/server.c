/*************************************************************************
	> File Name: server.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月10日 星期日 18时38分15秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/color.h"
#include "../common/udp_server.h"
#include "../common/thread_pool.h"
#include "../common/udp_epoll.h"
#include "../common/common.h"
#include "../common/game.h"

struct User *rteam;
struct User *bteam;

int repollfd, bepollfd;


char *conf = "./server.conf";

int port;

int main(int argc, char **argv) {
    int opt, listener, epoll_fd;
    pthread_t draw_t, red_t, blue_t, heart;
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

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));

    if((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    DBG(GREEN"INFO"NONE " : Server start on Port %d\n", port);

  //  pthread_create(&draw_t, NULL, draw, NULL);


    epoll_fd = epoll_create(MAX * 2);
    repollfd = epoll_create(MAX);
    bepollfd = epoll_create(MAX);

    if(epoll_fd || repollfd < 0 || bepollfd < 0) {
        perror("epoll_fd");
        exit(1);
    }

/*任务队列*/
    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);

/*sub_reactor从反应堆*/
    pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue);
    pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue);
    //pthread_create(&heart_t, NULL, head_beat, NULL);


/*主反应堆*/
    struct epoll_event ev, events[MAX * 2];
    ev.events = EPOLLIN;
    ev.data.fd = listener;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener, &ev);
    struct sockaddr_in client;
    socklen_t len = sizeof(client);



    while(1) {
    
        //w_gotoxy_puts(Message, 1, 1, "Waiting for login!");

        DBG(YELLOW"Main Thread"NONE" : before epoll_wait\n");
        int nfds = epoll_wait(epoll_fd, events, MAX * 2, -1);
        DBG(YELLOW"Main Thread"NONE" : After epoll_wait\n");

        for(int i = 0; i < nfds; i++) {

            struct User user;

            char buff[512] = {0};
            DBG(YELLOW"EPOLL"NONE" : Doing with %dth fd\n", i);
            if(events[i].data.fd == listener) {
                /*listen*/
                //accept();
                int new_fd = udp_accept(epoll_fd, listener, &user);
                if(new_fd > 0) {
                    DBG(YELLOW"Main Thread"NONE" : Add %s to %s sub_reactor.\n", user.name, (user.team ? "BLUE" : "RED"));
                    add_to_sub_reactor(&user);
                }
            } else {
                recv(events[i].data.fd, buff, sizeof(buff), 0);
                DBG(PINK"RECV"NONE" : %s\n", buff);
            }
        }
    }

    return 0;
}
