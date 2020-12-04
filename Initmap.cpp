//
// Created by Administrator on 2020/12/2.
//
#include "toolsFunction.h"
Node* initNode(){
    Node* p= newNode;
    p->firstEdge = nullptr;
    p->right = p->left = nullptr;
    p->rightTag = p->leftTag = 0;
    p->ID = -1;
    p->mainId = nodeNum;
    p->introduce = nullptr;
    p->sequenceNext = nullptr;
    ++nodeNum;
    return p;
}
void initEdge(Edge*cur,Node* tail,Node* top,int weight){
    cur->weight = weight;
    cur->next = nullptr;
    cur->tail = tail;
    cur->top = top;
}
void remoteNode(Node* tail,Node* top,int weight){
    Edge* cur = tail->firstEdge;
    if (cur == nullptr){
        cur = newEdge;
        initEdge(cur,tail,top,weight);
        tail->firstEdge = cur;
        return;
    }
    while(cur->next!=nullptr){
        cur = cur->next;
    }
    Edge* temp = newEdge;
    initEdge(temp,tail,top,weight);
    cur->next = temp;
    // 无向图第二次连接
    cur = top->firstEdge;
    if (cur == nullptr){
        cur = newEdge;
        top->firstEdge = cur;
        initEdge(cur,top,tail,weight);
        return;
    }
    while(cur->next!=nullptr){
        cur = cur->next;
    }
    temp = newEdge;
    cur->next = temp;
    initEdge(temp,top,tail,weight);
};
Node* createMap(){
    return initNode();
};
void pushSequenceNode(Node* head,Node* sign){
    Node* t = head;
    while(t->sequenceNext!=NULL){
        t = t->sequenceNext;
    }
    t->sequenceNext = sign;
}
void InsertNode(Node* root,Node* sign){
    if (root->ID >= sign->ID){
        if(root->left == nullptr){
            root->left = sign;
            return;
        }
        InsertNode(root->left,sign);
    }else{
        if(root->right == nullptr){
            root->right = sign;
            return;
        }
        InsertNode(root->right,sign);
    }
};
Node* searchNodeWithID(Node* root,int ID){
    if (root == nullptr || root->ID == ID){
        return root;
    }
    if(ID > root->ID){
        return searchNodeWithID(root->right,ID);
    }else{
        return searchNodeWithID(root->left,ID);
    }
};

Node* searchNodeWithName(Node* root,char* name){
    Node *p = preOrderTrailTree(root,name);
    return p;
};

void setName(Node* root,char* name){
    root->name = name;
};

void setIntroduce(Node* root,char* introduce){
    root->introduce = introduce;
};
void setID(Node* root,int ID){
    root->ID = ID;
}
