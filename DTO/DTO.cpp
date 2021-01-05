//
// Created by Administrator on 2020/12/17.
//

//
// Created by Administrator on 2020/12/17.
//
#include <cstring>
#include "DTO.h"
#include "./Stack/Stack.h"

/*��ȡ���ĳ���*/
int getNodeSize(Node *star){
    int num = 0;
    Edge *p = star->firstEdge;
    while(p!=NULL){
        ++num;
        p = p->next;
    }
    return num;
}
/*����Ѱ������֮�������·��*/
void  DFS(Stack* stack,Node* star,Node *end){
    if (star->ID == end->ID){
        printStack(stack);
        free(popStack(stack));
        return;
    }
    Edge* p = star->firstEdge;
    bool *rootVisited =(bool*) malloc(sizeof(bool)*NodeNum);
    if(getNodeSize(star) == 0){
        free(popStack(stack));
        return;
    }
    for (int i = 0; i < NodeNum; ++i) {
        rootVisited[i] = false;
    }
    rootVisited[star->mainId] = true;
    for (int i = 0; i < getNodeSize(star); ++i,p=p->next) {
        if(rootVisited[p->top->mainId] == false && !NodeInStack(stack,p->top)){
            rootVisited[p->top->mainId] = true;
            pushStack(stack,initStackNode(p->top));
            DFS(stack,p->top,end);
        }
    }
    free(popStack(stack));
}
/*�������֮�������·��*/
void printAllPath(Node *star,Node* end){
    if(star == NULL || end == NULL){
        printf("����δ֪�ص㣬��������\n");
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
            DFS(root,p->top,end);
        }
    }
}