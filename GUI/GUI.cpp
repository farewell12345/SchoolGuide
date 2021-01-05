//
// Created by Administrator on 2020/12/22.
//
#include "GUI.h"
#include "../ToolFunction/toolsFunction.h"
#include <cstdio>
#include "../KeyEvent/KeyEvent.h"
#define WindowWeight 1400
#define WindowHeight 840
#define nodeWeight 170
#define nodeHeight 50
#define MapLeft 0
#define MapRight 1020
#define MapTop 200
#define MapBottom 840
#define OKLEFT MapRight+140
#define OKRIGHT OKLEFT+100
#define OKTOP MapTop+360
#define OKBOTTOM OKTOP+40
static Node* mapStart;
static Node* mapEnd;
Stack* crux;
int canDrawPath = false;
int mouse_x = 0,mouse_y = 0; // 鼠标坐标位置
static int switchState = 0; // 选项状态
void drawTable(Node *head){
    setbkmode(TRANSPARENT);
    setcolor(EGERGB(0, 0, 0));
    setfont(20, 0, "楷体");
    setfontbkcolor(EGERGB(247, 238, 214));
    int left = 0,right = left+nodeWeight
            ,top = 0,down = top+nodeHeight;
    int num = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < NodeNum/4 + 1; ++j,num++) {
            setfillcolor(EGERGB(247, 238, 214));
            bar(left,top,right,down);
            if (num < NodeNum){

                if(NodeInStack(crux,head->sequenceNext[num])){
                    setfillcolor(EGERGB(255,255,0));
                    bar(left,top,right,down);
                }
                fillellipse(MapLeft+head->sequenceNext[num]->x,
                            MapTop + head->sequenceNext[num]->y,
                            10,10);
                setfillcolor(EGERGB(0xFF, 0x0, 0x0));
                outtextrect(left+20, top+10,
                            200,50, head->sequenceNext[num]->name);
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
void drawBackGround(){
    PIMAGE img = newimage();
    getimage(img,"F:\\Program\\Clion-Protect\\class_protect\\source\\平面图.jpg");
    putimage(0,200,img);
}
char *MenuButton[] = {"导航","途径多点最佳路径","两点间所有路径","退出"};
void drawMenu(){
    int left = MapRight+50,top = MapTop+110,right = MapRight+350,bottom =  MapTop+160;
    for (int i = 0; i < 4; ++i,top = bottom,bottom += 50) {
        bar(left,top+10,right,bottom);

    }
    left = MapRight+50,top = MapTop+110,right = MapRight+350,bottom =  MapTop+160;
    for (int i = 0; i < 4; ++i,top = bottom,bottom += 50) {
        outtextxy(left+50,top+20,MenuButton[i]);
    }
    FlushModeBehave(MenuButton[switchState]);
}
void FlushModeBehave(char mode[]){
    bar(MapRight+50,MapTop+320,MapRight+350,MapTop+340);
    char ModeBehave[50] = "目前处于：";
    strcat(ModeBehave,mode);
    outtextxy(MapRight+50,MapTop+320,ModeBehave);
}
void FlushMap(Node* head){
    setfillcolor(EGERGB(247, 238, 214));
    setbkcolor(WHITE);					//设置背景颜色为白色
    drawBackGround();
    drawTable(head);
    drawMenu();
    switch(switchState){
        case 1:
            DrawOk();
            break;
    }
}
void DrawTwoNodeShortPath(char* path,const Node* head,const Node*start,const Node*end){
    Stack *temp = createStack();
    getPath(temp,head,start->mainId-1,end->mainId-1);
    temp = reverseStack(temp);
    stackNode *next = nullptr;
    while (getTopStack(temp) != nullptr){
        stackNode *now = popStack(temp);
        if(getTopStack(temp) != nullptr){
            next = getTopStack(temp);
            setcolor(BLACK);
            setlinewidth(2);
            strcat(path,now->data->name);
            strcat(path,"->");
            if(next->next == nullptr){
                strcat(path,next->data->name);
            }
            line(MapLeft+now->data->x,MapTop+now->data->y,
                 MapLeft+next->data->x,MapTop+next->data->y);
        }
    }
}
void DrawPathText(char* path){
    setfillcolor(EGERGB(255, 255,255));
    bar(1020,0,1400,300);
    outtextrect(MapRight,150,350,150, path);
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
                if (getShortPath(mapEnd,mapStart)>=INF) {
                    strcat(text, "无法直接到达");
                    DrawPathText(text);
                    return;
                }else{
                    strcat(text, "的最短路径长为:");
                    itoa(getShortPath(mapEnd, mapStart), shortPath, 10);
                    strcat(text, shortPath);
                    strcat(text,"\n路径为：\n");
                    setcolor(EGERGB(255, 0, 0));
                    DrawTwoNodeShortPath(text,head,mapEnd,mapStart);
                    DrawPathText(text);
                    mapStart = nullptr;
                    mapEnd = nullptr;
                    return;
                }
            }else {
                strcat(text, "的最短路径长为:");
                itoa(getShortPath(mapStart, mapEnd), shortPath, 10);
                strcat(text, shortPath);
            }
            strcat(text,"\n路径为：\n");
            setcolor(EGERGB(255, 0, 0));
            DrawTwoNodeShortPath(text,head,mapStart,mapEnd);
            DrawPathText(text);
            mapStart = nullptr;
            mapEnd = nullptr;
        }
    }
}
Stack* manyNode = createStack();
void ManyNodeGuide(Node*head,Stack* nodeStack,Node* nowNode){
    if (NodeInStack(nodeStack,nowNode)){
        return;
    }
    pushStack(nodeStack,initStackNode(nowNode));
    char text[256] = "已选择：";
    stackNode *temp = getTopStack(nodeStack);
    while(temp!=nullptr){
        strcat(text,temp->data->name);
        strcat(text,"->");
        temp = temp->next;
    }
    cleardevice();
    FlushMap(head);
    outtextrect(MapRight+50,MapTop,200,200, text);
}
void showInfo(Node*nowNode){
    char info[256];
    strcpy(info,nowNode->name);
    strcat(info,":");
    strcat(info,nowNode->introduce);
    setfillcolor(EGERGB(255, 255,255));
    setbkcolor(EGERGB(255,255,255));
    outtextrect(1100,50,200,100,info);
}
void DrawOk(){
    setfillcolor(EGERGB(102,204,255));
    bar(OKLEFT,OKTOP,OKRIGHT,OKBOTTOM);
    setcolor(EGERGB(255,255,255));
    if (switchState == 1){
        outtextxy(OKLEFT+10,OKTOP,"确定");
    }
    setcolor(EGERGB(0,0,0));
    setfillcolor(EGERGB(247, 238, 214));
}
void drawPathStack(Stack *stack){
    stackNode *now = getTopStack(stack),*next = now->next;
    while (next!=nullptr){
        line(MapLeft+now->data->x,MapTop+now->data->y,
             MapLeft+next->data->x,MapTop+next->data->y);
        now = next;
        next = next->next;
    }
}
void printRoad(Stack* stack){
    stackNode * t = stack->top;
    Stack *temp = createStack();
    while (t!=NULL){
        pushStack(temp,initStackNode(t->data));
        t = t->next;
    }
    char text[256] = "";
    drawPathStack(temp);
    while(!StackIsEmpty(temp)){
        stackNode* p = popStack(temp);
        strcat(text,p->data->name);
        strcat(text,"->");
        free(p);
    }
    strcat(text,"\n按任意键查看下一条路径,按A终止");
    DrawPathText(text);
}
char exitFlag = 0;
void MapDFS(Node* head,Stack* stack,Node* star,Node *end) {
    if(exitFlag == 'A'){
        mapStart = nullptr;
        mapEnd = nullptr;
        return;
    }
    if (star->ID == end->ID) {
        printStack(stack);
        printRoad(stack);
        exitFlag = getch();
        cleardevice();
        FlushMap(head);
        free(popStack(stack));
        return;
    }
    Edge *p = star->firstEdge;
    bool *rootVisited = (bool *) malloc(sizeof(bool) * NodeNum);
    if (getNodeSize(star) == 0) {
        free(popStack(stack));
        return;
    }
    for (int i = 0; i < NodeNum; ++i) {
        rootVisited[i] = false;
    }
    rootVisited[star->mainId] = true;
    for (int i = 0; i < getNodeSize(star); ++i, p = p->next) {
        if (rootVisited[p->top->mainId] == false && !NodeInStack(stack, p->top)) {
            rootVisited[p->top->mainId] = true;
            pushStack(stack, initStackNode(p->top));
            MapDFS(head,stack, p->top, end);
        }
    }
    free(popStack(stack));
}
void TwoNodeAllPath(Node* head,Node *star,Node* end){
    if(star == NULL || end == NULL){
        printf("含有未知地点，请检查输入\n");
        return;
    }
    Stack* root = createStack();
    pushStack(root,initStackNode(star));
    Edge* p = star->firstEdge;
    bool *rootVisited = (bool *)malloc(sizeof(bool)*NodeNum);
    for (int i = 0; i < NodeNum; ++i) {
        rootVisited[i] = false;
    }
    rootVisited[star->mainId-1] = true;
    for (int i = 0; i < getNodeSize(star); ++i,p=p->next) {
        if(rootVisited[p->top->mainId] == false && !NodeInStack(root,p->top)){
            rootVisited[p->top->mainId] = true;
            pushStack(root,initStackNode(p->top));
            MapDFS(head,root,p->top,end);
        }
    }
}

void initWindows(Node* head){
    crux = KeyEvent(head);
    initgraph(WindowWeight, WindowHeight,INIT_RENDERMANUAL);
    mapEnd = mapStart = nullptr;
    //初始化图形界面
    FlushMap(head);
    for (; is_run(); delay_fps(90)) {
        while(getmouse().is_left()) {
            mousepos(&mouse_x, &mouse_y);
            if (mouse_x <= 1200 && mouse_y <= 200) {
                int i = (mouse_y / 50) * 6 + mouse_x / 170;
                if(i >= NodeNum)break;
                Node *nowNode = head->sequenceNext[i];
                showInfo(nowNode);
                switch(switchState){
                    case 0:
                        Guide(head,nowNode);
                        break;
                    case 1:
                        canDrawPath = false;
                        ManyNodeGuide(head,manyNode,nowNode);
                        break;
                    case 2:
                        if (mapStart == nullptr) {
                            mapStart = nowNode;
                            break;
                        } else if (mapEnd == nullptr) {
                            mapEnd = nowNode;
                            if (mapEnd->ID == mapStart->ID) {
                                mapEnd = nullptr;
                                break;
                            }
                        }
                        exitFlag = 0;
                        TwoNodeAllPath(head,mapStart,mapEnd);
                    default:
                        break;
                }
            }else if(mouse_x >= MapRight+50 && mouse_x <= MapRight + 350 &&
            MapTop+110 <= mouse_y && mouse_y <= MapTop + 110 + 240)
            {
                    switchState = (mouse_y - (MapTop+110)) / 60;
                    printf("点击了第%d",switchState);
                    switch (switchState){
                        case 0:
                            clear(head);
                            break;
                        case 1:
                            clear(head);
                            DrawOk();
                            break;
                        case 2:
                            clear(head);
                            break;
                        case 3:
                            exit(1);
                    }
                    FlushModeBehave(MenuButton[switchState]);
            }
            else if(OKLEFT<=mouse_x && OKTOP <= mouse_y && mouse_y <= OKBOTTOM && mouse_x <= OKRIGHT){
                printf("点击确定\n");
                int NodeSize = getStackSize(manyNode);
                if((NodeSize<2) && !canDrawPath){
                    continue;
                }else if (NodeSize < 2){
                    continue;
                }else{
                    canDrawPath = true;
                }
                Node** p =(Node**) malloc(sizeof(Node*)*NodeSize);
                stackNode *temp = popStack(manyNode);
                for (int i = 0; i < NodeSize; ++i) {
                    p[i] = temp->data;
                    if (getTopStack(manyNode) == NULL){
                        break;
                    }
                    temp = popStack(manyNode);
                }
                char path[10000]="";
                Stack*shortedMap = createShortedMap(p,NodeSize);
                if(shortedMap==NULL){
                    break;
                }
                stackNode *next = getTopStack(shortedMap);
                while(next!=nullptr) {
                    stackNode *now = next;
                    next = next->next;
                    if (next == nullptr || next->next == nullptr){
                        canDrawPath = false;
                        break;
                    }
                    printf("%s->%s\n",now->data->name,next->data->name);
                    int flag = false;
                    if(next->next==nullptr){
                        flag = true;
                    }
                    if(getShortPath(now->data,next->data) <INF) {
                        DrawTwoNodeShortPath(path, head, now->data, next->data);
                    }else{
                        DrawTwoNodeShortPath(path, head, next->data, now->data);;
                    }
                    if (flag == true){
                        canDrawPath = false;
                        break;
                    }
                }
            }
        }
    }
    closegraph();						//关闭图形界面
};
void clear(Node* head){
    mapStart = nullptr;
    mapEnd = nullptr;
    cleardevice();
    FlushMap(head);
    freeStack(manyNode);
    setfillcolor(EGERGB(255, 255,255));
    bar(OKLEFT,OKTOP,OKRIGHT,OKBOTTOM);
    setfillcolor(EGERGB(247, 238, 214));
}