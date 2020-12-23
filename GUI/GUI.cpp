//
// Created by Administrator on 2020/12/22.
//
#include "GUI.h"
#include <cstdio>
#define WindowWeight 1400
#define WindowHeight 960

void initWindows(){
    PIMAGE img = newimage();
    initgraph(WindowWeight, WindowHeight,INIT_RENDERMANUAL);
    getimage(img,"F:\\Program\\Clion-Protect\\class_protect\\source\\平面图.jpg");
    //初始化图形界面
    setcolor(EGERGB(0xFF, 0x0, 0x0));	//设置绘画颜色为红色

    setbkcolor(WHITE);					//设置背景颜色为白色
    putimage(0,200,img);
    getch();							//暂停，等待键盘按键

    closegraph();						//关闭图形界面
};

