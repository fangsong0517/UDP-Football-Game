/*************************************************************************
	> File Name: thread_pool.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月21日 星期四 21时42分29秒
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include "head.h"
#define MAXTASK 100
#define MAXTHREAD 10
struct task_queue {
    int sum;
    int epollfd;
    struct User **team;
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User *user);
struct User *task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);


#endif
