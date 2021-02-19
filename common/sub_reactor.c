/*************************************************************************
	> File Name: sub_reactor.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月23日 星期六 20时08分52秒
 ************************************************************************/

#include "head.h"
#include "thread_pool.h"
#include "sub_reactor.h"
#define MAX 50



void *sub_reactor(void *arg) {
    struct task_queue *taskQueue = (struct task_queue *)arg;
    pthread_t *tid = (pthread_t *)calloc(MAXTHREAD, sizeof(pthread_t));
    for(int i = 0; i < MAXTHREAD; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)taskQueue);
    }
    struct epoll_event ev, events[MAX];
    int nfds;
    while(1) {
        DBG(RED"Sub Reactor: "NONE "Epoll wating...\n");
        nfds = epoll_wait(taskQueue->epollfd, events, MAX, -1);
        if(nfds == -1) {
            perror("epoll_wait");
            exit(1);
        }
        for(int i = 0; i < nfds; i++) {
            struct User *user = (struct User *)events[i].data.ptr;
            DBG(L_YELLOW"events[n].data.ptr->name = %s \n"NONE, user->name);
            if(events[i].events & EPOLLIN) {
                task_queue_push(taskQueue, (struct User *)events[i].data.ptr);
            }
        }
    }
    return NULL;
}

