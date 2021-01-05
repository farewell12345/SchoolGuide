//
// Created by Administrator on 2020/12/2.
//
#include <string.h>
#include "../ToolFunction/toolsFunction.h"
/*初始化结点*/
Node* initNode(Node* p){
    p->firstEdge = NULL;
    p->right = p->left = NULL;
    p->rightTag = p->leftTag = 0;
    p->ID = -1;
    p->mainId = NodeNum;
    p->sequenceNext = NULL;
    ++NodeNum;
    return p;
}
/*初始化无向边*/
void initEdge(Edge*cur,Node* tail,Node* top,int weight){
    cur->weight = weight;
    cur->next = NULL;
    cur->tail = tail;
    cur->top = top;
}
/*连接两个顶点（无向图）*/
void remoteNode(Node* tail,Node* top,int weight){
    Edge* cur = tail->firstEdge;
    if (cur == NULL){ // 如果顶点度为0
        cur = newEdge;
        initEdge(cur,tail,top,weight); // 初始化无向边
        tail->firstEdge = cur; // 连接
        return;
    }
    while(cur->next!= NULL){
        cur = cur->next;
    }
    Edge* temp = newEdge;
    initEdge(temp,tail,top,weight);
    cur->next = temp; // 连到最后面
    // 无向图第二次连接，把起点连入终点的度里面
    cur = top->firstEdge;
    if (cur == NULL){
        cur = newEdge;
        top->firstEdge = cur;
        initEdge(cur,top,tail,weight);
        return;
    }
    while(cur->next!=NULL){
        cur = cur->next;
    }
    temp = newEdge;
    cur->next = temp;
    initEdge(temp,top,tail,weight);
};
Node* createMap(Node *p){
    return initNode(p);
};
/*把结点压入结点顺序表中，顺序表作用：辅助多源最短路径算法*/
Node* pushSequenceNode(Node* head,Node* sign){
    if (NodeNum <= 1){
        sign->sequenceNext = head->sequenceNext;
        *head = *sign;
        return head;
    }
    head->sequenceNext[NodeNum-2] = sign;
    return head;
}
/*构建搜索二叉树*/
/*设置结点名字*/
void setName(Node* root,char* name){
    strcpy(root->name,name);
}
/*设置结点介绍信息*/
void setIntroduce(Node* root,char* introduce){
    strcpy(root->introduce,introduce);
}
/*设置结点ID*/
void setID(Node* root,int ID){
    root->ID = ID;
}