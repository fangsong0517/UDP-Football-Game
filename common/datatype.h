/*************************************************************************
	> File Name: datatype.h
	> Author:fangsong
	> Mail: fsrun@outlook.com
	> Created Time: 2021年01月11日 星期一 14时00分01秒
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H

struct Point{
    int x;
    int y;
};

struct User{
    int team;
    char name[20];
    int flag;       /*未响应的次数*/
    struct sockaddr_in addr;
    struct Point loc;
};

struct Map{          /*地图信息*/
    int width;       /*宽度*/
    int height;      /*高*/
    struct Point start; /*开始的位置*/
    int gate_width;
    int gate_height;
};


struct Ctrl {        /*控制*/
    int carry;       /*带球*/
    int kick;        /*踢球*/
};

struct TransMsg{   /*传的信息*/
    int dirx;      /*方向*/
    int diry;      /*方向*/
    struct Ctrl ctrl; /*控球*/
};



#endif
