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
    getimage(img,"F:\\Program\\Clion-Protect\\class_protect\\source\\ƽ��ͼ.jpg");
    //��ʼ��ͼ�ν���
    setcolor(EGERGB(0xFF, 0x0, 0x0));	//���û滭��ɫΪ��ɫ

    setbkcolor(WHITE);					//���ñ�����ɫΪ��ɫ
    putimage(0,200,img);
    getch();							//��ͣ���ȴ����̰���

    closegraph();						//�ر�ͼ�ν���
};

