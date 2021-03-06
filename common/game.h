/*************************************************************************
	> File Name: game.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月11日 星期一 15时20分57秒
 ************************************************************************/

#ifndef _GAME_H
#define _GAME_H


#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)
#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, Message),DEFARG(arg1, NULL), arg2, DEFARG(arg3, 0))

#define MAX 50

struct Map court;/*球场*/


WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
WINDOW *create_newwin(int width, int height, int startx, int starty);

void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, char c);
void gotoxy_puts(int x, int y, char *s);
void w_gotoxy_putc(WINDOW *win, int x, int y, char c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();
void init_help();
void *draw(void *arg);

void show_message(WINDOW *win, struct User *user, char *msg, int type);
#endif
