//
// Created by Administrator on 2020/12/22.
//
#include "GUI.h"
#include "../ToolFunction/toolsFunction.h"
#include <cstdio>
#define WindowWeight 1400
#define WindowHeight 840
#define nodeWeight 170
#define nodeHeight 50
#define MapLeft 0
#define MapRight 1020
#define MapTop 200
#define MapBottom 840
static Node* mapStart;
static Node* mapEnd;
static int switchState; // ѡ��״̬
void drawTable(Node *head){
    setbkmode(TRANSPARENT);
    setcolor(EGERGB(0, 0, 0));
    setfont(20, 0, "����");
    setfontbkcolor(EGERGB(247, 238, 214));
    int left = 0,right = left+nodeWeight,top = 0,down = top+nodeHeight;
    int num = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < NodeNum/4 + 1; ++j,num++) {
            setfillcolor(EGERGB(247, 238, 214));
            bar(left,top,right,down);
            if (num < NodeNum){
                outtextrect(left+20, top+10,200,50, head->sequenceNext[num]->name);
                setfillcolor(EGERGB(0xFF, 0x0, 0x0));
                fillellipse(MapLeft+head->sequenceNext[num]->x,MapTop + head->sequenceNext[num]->y,10,10);
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
    char *text[] = {"����",";��������·��","���������·��","�˳�"};
    int left = MapRight+50,top = MapTop+110,right = MapRight+350,bottom =  MapTop+160;
    for (int i = 0; i < 4; ++i,top = bottom,bottom += 50) {
        bar(left,top+10,right,bottom);

    }
    left = MapRight+50,top = MapTop+110,right = MapRight+350,bottom =  MapTop+160;
    for (int i = 0; i < 4; ++i,top = bottom,bottom += 50) {
        outtextxy(left+50,top+20,text[i]);
    }
}
void FlushMap(Node* head){
    setfillcolor(EGERGB(247, 238, 214));
    setbkcolor(WHITE);					//���ñ�����ɫΪ��ɫ
    drawBackGround(head);
    drawTable(head);
    drawMenu();
}
void Guide(Node*head,Node* nowNode){
    if (mapStart == nullptr) {
        mapStart = nowNode;
    } else if (mapEnd == nullptr) {
        mapEnd = nowNode;
        if (mapEnd->ID == mapStart->ID){
            mapEnd = nullptr;
            return;
        }
        if(mapStart != nullptr && mapEnd != nullptr) {
            cleardevice();
            FlushMap(head);
            char text[256];
            strcpy(text, mapStart->name);
            strcat(text, "->");
            strcat(text, mapEnd->name);
            char shortPath[10];
            if(getShortPath(mapStart, mapEnd) >=INF){
                strcat(text,"�޷�ֱ�ӵ���");
            }else {
                strcat(text, "�����·����Ϊ:");
                itoa(getShortPath(mapStart, mapEnd), shortPath, 10);
                strcat(text, shortPath);
            }
            setcolor(EGERGB(255, 0, 0));
            outtextrect(MapRight+50,MapTop,200,200, text);
            Stack *temp = createStack();
            getPath(temp,head,mapStart->mainId-1,mapEnd->mainId-1);
            while (getTopStack(temp) != nullptr){
                stackNode *now = popStack(temp);
                if(getTopStack(temp) != nullptr){
                    stackNode *next = getTopStack(temp);
                    setcolor(BLACK);
                    setlinewidth(2);
                    line(MapLeft+now->data->x,MapTop+now->data->y,
                         MapLeft+next->data->x,MapTop+next->data->y);
                    free(now);
                }
            }
            free(temp);
            mapStart = nullptr;
            mapEnd = nullptr;
        }
    }
}
void initWindows(Node* head){

    initgraph(WindowWeight, WindowHeight,INIT_RENDERMANUAL);
    mapEnd = mapStart = nullptr;
    //��ʼ��ͼ�ν���
    FlushMap(head);
    int mouse_x = 0,mouse_y = 0;
    switchState = 1;
    for (; is_run(); delay_fps(60)) {
        if(getmouse().is_left()) {
            mousepos(&mouse_x, &mouse_y);
            if (mouse_x <= 170 * 6 && mouse_y <= 200) {
                Node *nowNode = head->sequenceNext[(mouse_y / 50) * 6 + mouse_x / 170];
                char info[256];
                strcpy(info,nowNode->name);
                strcat(info,":");
                strcat(info,nowNode->introduce);
                outtextrect(1100,50,200,200,info);
                switch(switchState){
                    case 1:
                        Guide(head,nowNode);
                        break;
                    default:
                        break;
                }
            }else if(mouse_x){

            }
        }

    }
    getch();							//��ͣ���ȴ����̰���
    closegraph();						//�ر�ͼ�ν���
};

