//
// Created by Administrator on 2020/12/2.
//
/*线索化二叉树*/
#include "toolsFunction.h"
#include <cstring>
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9') // 宏定义判断一个字符是不是数字

int abs(int c){
    return c<0? c*-1:c;
}

// 全局的结点数
extern int **shortPath; // 距离向量数组
extern int **path; // 路径向量数组
Node *visited[23]; // 访问标记
int visitedNum = 0; // 已访问的数量
/* 判断字符串是否为数*/
int is_number(char * s)
{
    bool flag = true;
    for (int i = 0; i < strlen(s); ++i) {
        if(!IS_DIGIT(s[i])){
            flag = false;
        }
    }
    return flag;
}
/*判断结点是否被访问过*/
bool NodeIsVisited(Node* Nodes){
    for (int i = 0; i < visitedNum; ++i) {
        if (visited[i]==Nodes){
            return true;
        }
    }
    return false;
}
/* 获取任意两个结点之间的距离，如果不相连就返回INF（INTMAX）*/
int getWeight(Node* tail,Node* top){
    Edge *e = tail->firstEdge;
    while(e!=NULL){
        if (e->top == top){
            return e->weight;
        }
        e = e->next;
    }
    return INF;
}
/*根据路径向量获取两点之间的最短路径并输出*/
void getPath(Stack* stack,const Node *head,int start,int end){ // 递归输出沿路路径
    if (start == path[start][end]){ // 此处说明回到了起点，则结束递归，从起点开始输出路径
        pushStack(stack,initStackNode(getNode(head,start)));
        pushStack(stack,initStackNode(getNode(head,end)));
    }else{
        getPath(stack,head,start,path[start][end]); // 一直回溯找下去
        pushStack(stack,initStackNode(getNode(head,end)));
    }
}
// 深搜打印景点信息表
void dfs(Node* cur) {
    if (NodeIsVisited(cur) == true) return;
    visited[visitedNum-1] = cur;
    visitedNum++;
    Edge *edge = cur->firstEdge;
    while (edge != NULL) {
        if(NodeIsVisited(edge->top) == false) {
            printf("%s", edge->top->name);
            for (int i = 0; i < (20-strlen(edge->top->name)); ++i) {
                printf(" ");
            }
            printf("|\tID:%d\t|\n",edge->top->ID);
            dfs(edge->top);
        }
        edge = edge->next;
    }
}
/*根据主键获取结点*/
Node *getNode(const Node *head, int i){
    return head->sequenceNext[i];
}
/*多源最短路径算法*/
void Floyd(Node* head) {
    /*分配空间*/
    shortPath = (int **) malloc(sizeof(int *) * NodeNum);
    path = (int **) malloc(sizeof(int *) * NodeNum);
    for (int i = 0; i < NodeNum; ++i) {
        shortPath[i] = (int *) malloc(sizeof(int)*NodeNum);
        path[i] = (int *) malloc(sizeof(int)*NodeNum);
    }
    for (int i = 0; i < NodeNum; ++i) {
        for (int j = 0; j < NodeNum; ++j) {
            if (i == j) {
                shortPath[i][j] = 0; // 顶点到自身的距离 = 0
            } else {
                shortPath[i][j] = getWeight(getNode(head, i), getNode(head, j)); // 讲i点到j点的距离权值存入数组
            }
            path[i][j] = i; // 此时i->j经过 i
        }
    }

    int temp;
    for (int k = 0; k < NodeNum; ++k) { // 中间点
        // 固定K为中间路径点，查看i到k和j到k能否形成通路，若能形成通路，再把路径大小与k点加入临时数组
        for (int i = 0; i < NodeNum; ++i) {
            for (int j = 0; j < NodeNum; ++j) {
                temp = (shortPath[i][k] == INF || shortPath[k][j] == INF) ? INF : (shortPath[i][k] + shortPath[k][j]); // 判定
                if (shortPath[i][j] > temp) { // 如果temp比原有路径短就替换
                    shortPath[i][j] = temp;
                    path[i][j] = path[k][j]; // 把K点加入路径
                }
            }
        }
    }
}
void freeStack(Stack *head){
    if (head == nullptr)return;
    if (getTopStack(head) == NULL){
        return;
    }
    stackNode * p= popStack(head);
    while (p!=nullptr){
        if(getTopStack(head)!=nullptr) {
            p = popStack(head);
        }else{
            break;
        }
    }
}
/*获取两点间的最短路径长度（在跑完Floyd以后）*/
int getShortPath(Node* star,Node* end){
    return shortPath[star->mainId-1][end->mainId-1];
}
bool NodeArrayIsEmpty(Node** root,int NodeSize){
    for (int i = 0; i < NodeSize; ++i) {
        if (root[i]!=nullptr){
            return false;
        }
    }
    return true;
}
/*途径多个点的最佳路径计算*/
Stack * createShortedMap(Node** root,int NodeSize){
    Stack* vector = createStack();
    Node *now = root[0];
    int min = -1;
    pushStack(vector,initStackNode(now));
    while (!StackIsFull(vector,NodeSize)){
        for (int i = 0; i < NodeSize; ++i) {
            if (NodeInStack(vector,root[i])){
                continue;
            }
            if(min == -1){
                min = i;
                continue;
            }
            if(getShortPath(now,root[min]) < getShortPath(now,root[i])){
                min = i;
            }
        }
        if(min == -1){
            break;
        }
        pushStack(vector,initStackNode(root[min]));
        now = root[min];
        min = -1;
    }
    return vector;
}