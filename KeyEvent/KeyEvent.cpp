//
// Created by Administrator on 2021/1/4.
//
#include "KeyEvent.h"
Node** Visited;//记录走过的顶点
int __VisitedNum = 1;
bool __NodeIsVisited(Node* p){
    for (int i = 0; i < __VisitedNum; ++i) {
        if(Visited[i]==p){
            return true;
        }
    }
    return false;
}
Stack *__crux = createStack(); // 关键结点数组
void __dfs(Node* cur) {
    if (__NodeIsVisited(cur) == true) return;
    Visited[__VisitedNum-1] = cur;
    __VisitedNum++;
    Edge *edge = cur->firstEdge;
    while (edge != NULL) {
        if(__NodeIsVisited(edge->top) == false) {
            if (cur->left!=NULL && cur->right!=NULL && cur->leftTag + cur->rightTag == 0){
                pushStack(__crux,initStackNode(cur));
            }
            __dfs(edge->top);
        }
        edge = edge->next;
    }
}
Stack* KeyEvent(Node* head){
    Visited =(Node**) malloc(sizeof(Node*)*NodeNum);
    for (int i = 0; i < NodeNum; ++i) {
        if(!__NodeIsVisited(head->sequenceNext[i])){
            __dfs(head->sequenceNext[i]);
        }
    }
    return __crux;
}