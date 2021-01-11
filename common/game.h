/*************************************************************************
	> File Name: game.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月11日 星期一 15时20分57秒
 ************************************************************************/

#ifndef _GAME_H
#define _GAME_H

struct Map court;/*球场*/

WINDOW *create_newwin(int width, int height, int startx, int starty);

void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, char c);
void gotoxy_puts(int x, int y, char *s);
void w_gotoxy_putc(WINDOW *win, int x, int y, char c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();
void *draw(void *arg);

#endif
