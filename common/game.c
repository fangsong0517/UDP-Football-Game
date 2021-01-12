/*************************************************************************
	> File Name: game.c
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月11日 星期一 15时21分02秒
 ************************************************************************/


#include "head.h"

extern struct Map court;
extern WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
WINDOW *create_newwin(int width, int height, int startx, int starty) {
    WINDOW *win;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);
    move(LINES - 1, 1);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');/*清除线*/
    wrefresh(win);
    delwin(win);
}


void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, char c) {
    move(y, x);
    addch(c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char *s) {
    move(y, x);
    addstr(s);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, char c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void initfootball() {
    initscr();
    clear();
    if(!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色!\n");
        exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);    
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);    
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_GREEN);
    init_pair(8, COLOR_BLUE, COLOR_RED);
    init_pair(9, COLOR_BLUE, COLOR_WHITE);
    init_pair(10, COLOR_BLUE, COLOR_YELLOW);
    init_pair(11, COLOR_BLUE, COLOR_CYAN);
    init_pair(12, COLOR_BLUE, COLOR_BLUE);
    create_newwin(court.width + 4, court.height + 2, court.start.x - 2, court.start.y - 1);
    create_newwin(court.width + 4, 7, court.start.x - 2, court.start.y + court.height + 1);
    create_newwin(20, court.height + 2, court.start.x + court.width + 2, court.start.y - 1);
    create_newwin(20, 7, court.start.x + court.width + 2, court.start.y + court.height + 1);
   Message = create_newwin(court.width + 24, 5, court.start.x - 2, court.start.y + 1 + court.height + 7);

}

void *draw(void *arg) {
    initfootball();
    while(1) {
        sleep(10);
    }
}
