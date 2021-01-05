//
// Created by Administrator on 2020/12/2.
//
#include <string.h>
#include "../ToolFunction/toolsFunction.h"
/*��ʼ�����*/
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
/*��ʼ�������*/
void initEdge(Edge*cur,Node* tail,Node* top,int weight){
    cur->weight = weight;
    cur->next = NULL;
    cur->tail = tail;
    cur->top = top;
}
/*�����������㣨����ͼ��*/
void remoteNode(Node* tail,Node* top,int weight){
    Edge* cur = tail->firstEdge;
    if (cur == NULL){ // ��������Ϊ0
        cur = newEdge;
        initEdge(cur,tail,top,weight); // ��ʼ�������
        tail->firstEdge = cur; // ����
        return;
    }
    while(cur->next!= NULL){
        cur = cur->next;
    }
    Edge* temp = newEdge;
    initEdge(temp,tail,top,weight);
    cur->next = temp; // ���������
    // ����ͼ�ڶ������ӣ�����������յ�Ķ�����
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
/*�ѽ��ѹ����˳����У�˳������ã�������Դ���·���㷨*/
Node* pushSequenceNode(Node* head,Node* sign){
    if (NodeNum <= 1){
        sign->sequenceNext = head->sequenceNext;
        *head = *sign;
        return head;
    }
    head->sequenceNext[NodeNum-2] = sign;
    return head;
}
/*��������������*/
/*���ý������*/
void setName(Node* root,char* name){
    strcpy(root->name,name);
}
/*���ý�������Ϣ*/
void setIntroduce(Node* root,char* introduce){
    strcpy(root->introduce,introduce);
}
/*���ý��ID*/
void setID(Node* root,int ID){
    root->ID = ID;
}