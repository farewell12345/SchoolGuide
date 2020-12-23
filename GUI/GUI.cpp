//
// Created by Administrator on 2020/12/22.
//
#include "GUI.h"
#include <cstdio>
#define WindowWeight 1400
#define WindowHeight 840
#define nodeWeight 170
#define nodeHeight 50
#define MapLeft 0
#define MapRight 1020
#define MapTop 200
#define MapBottom 840
void drawTable(Node *head){
    setbkmode(TRANSPARENT);
    setcolor(EGERGB(247, 238, 214));
    setfont(20, 0, "����");
    setfontbkcolor(EGERGB(247, 238, 214));
    int left = 0,right = left+nodeWeight,top = 0,down = top+nodeHeight;
    int num = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < NodeNum/4 + 1; ++j) {
            bar(left,top,right,down);
            if (num < NodeNum){
                outtextxy(left+20, top+10, head->sequenceNext[num++]->name);
            }
            left = right;
            right += nodeWeight;
        }
        left = 0;
        right = left+nodeWeight;
        top = down;
        down += nodeHeight;
    }
}
void drawBackGround(Node* head){
    PIMAGE img = newimage();
    getimage(img,"F:\\Program\\Clion-Protect\\class_protect\\source\\ƽ��ͼ.jpg");
    putimage(0,200,img);
}
void drawMenu(){

}
void initWindows(Node* head){

    initgraph(WindowWeight, WindowHeight,INIT_RENDERMANUAL);

    //��ʼ��ͼ�ν���

    setfillcolor(EGERGB(0x0, 0x80, 0x80));
    setbkcolor(WHITE);					//���ñ�����ɫΪ��ɫ
    drawTable(head);
    drawBackGround(head);
    getch();							//��ͣ���ȴ����̰���

    closegraph();						//�ر�ͼ�ν���
};

