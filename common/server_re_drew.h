/*************************************************************************
	> File Name: server_re_drew.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年02月19日 星期五 10时49分30秒
 ************************************************************************/

#ifndef _SERVER_RE_DREW_H
#define _SERVER_RE_DREW_H
void re_drew_player(int team, char *name, struct Point *loc);
void re_drew_team(struct User *team);
void re_draw_ball();
void init_score();
void re_drew();
#endif

