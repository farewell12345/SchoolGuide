//
// Created by Administrator on 2020/12/2.
//
/*线索化二叉树*/
#include "toolsFunction.h"
#include <string.h>
extern NodeNum;
int visitedNum = 0;
Node *visited[23];
int **shortPath,**path;
bool NodeIsVisited(Node* Nodes){
    for (int i = 0; i < visitedNum; ++i) {
        if (visited[i]==Nodes){
            return true;
        }
    }
    return false;
}
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
void getPath(Node *head,int start,int end){ // 递归输出沿路路径
    if (start == path[start][end]){ // 此处说明回到了起点，则结束递归，从起点开始输出路径
        printf("%s->%s->",getNode(head,start)->name,getNode(head,end)->name);
    }else{
        getPath(head,start,path[start][end]); // 一直回溯找下去
        printf("%s->",getNode(head,end)->name); // 到达这里时说明找到了起点，从起点开始输出路径
    }
}
void dfs(Node* cur) {
    if (NodeIsVisited(cur) == true) return;
    visited[visitedNum-1] = cur;
    visitedNum++;
    Edge *edge = cur->firstEdge;
    while (edge != NULL) {
        if(NodeIsVisited(edge->top) == false) {
            printf("%s\n", edge->top->name);
            dfs(edge->top);
        }
        edge = edge->next;
    }
}

Node *getNode(Node *head, int i){
    return head->sequenceNext[i];
};

bool equals(char* name1,char* name2){
    return strcmp(name1,name2) == 0? true:false;
};

Node *prev; // 上次访问的节点(前驱节点）
Node * frontOrderTrailTree(Node *head){
    if(head == NULL) return head;

    if(head->left == NULL){ // 遵循左前右后
        head->left = prev; // 将空闲的左节点指向前驱节点
        head->leftTag = 1; // 表示这个节点的左指针已被线索化
    }
    if(prev != NULL && prev->right == NULL){
        prev->right = head; // 将空闲的右节点指向后继节点
        prev ->rightTag = 1;// 表示这个节点的右指针已被线索化
    }

    prev = head; // 线索化后将prev移动过来，开始寻找head的下一个后继节点
    if(head->leftTag == 0){ // 判断当前节点的左节点有没有线索化过
        head->left = frontOrderTrailTree(head->left);// 搜寻左子树
    }
    if(head->rightTag == 0){
        head->right = frontOrderTrailTree(head->right); // 搜寻右子树
    }
    return head;
}
/*遍历查找*/
Node *preOrderTrailTree(Node *head,char *name){
    Node* cur = head;
    /*不断沿着节点往下遍历，直到所有节点全部被遍历
     * 线索化以后，树的最后一个节点的右孩子（后继节点）为NULL*/
    while (cur!=NULL)
    {
        while (cur->leftTag == 0)
        {
            if (equals(name,cur->name)){
                return cur;
            }
            cur = cur->left; // 沿着左孩子向下遍历直到底部
        }
        if (equals(name,cur->name)){
            return cur;
        }
        cur = cur->right; // 沿着右孩子寻找后继节点
    }
    free(cur);
    return NULL;
}

void printMap(Node *head){
    for (int i = 0; i < NodeNum; ++i) {
        visited[i]=NULL;
    }
    Node* cur = head;
    /*不断沿着节点往下遍历，直到所有节点全部被遍历
     * 线索化以后，树的最后一个节点的右孩子（后继节点）为NULL*/
    while (cur!=NULL)
    {
        while (cur->leftTag == 0)
        {
            dfs(cur);
            cur = cur->left; // 沿着左孩子向下遍历直到底部
        }
        dfs(cur);
        cur = cur->right; // 沿着右孩子寻找后继节点
    }
};

void Floyd(Node* head) {
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

void printShortPath(Node*head,Node* star,Node* end){
    int i = star->mainId-1,j = end ->mainId-1;
    if (shortPath[i][j] < INF) {
        printf("%s->%s:%d   road: ", star->name, end->name, shortPath[i][j]); // 获取i点到j点的最短路径
    }
    getPath(head,i,j); // 输出i点到j点的路径
    printf("\n");
};