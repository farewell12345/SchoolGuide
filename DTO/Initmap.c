//
// Created by Administrator on 2020/12/2.
//
#include <string.h>
#include "../ToolFunction/toolsFunction.h"
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
void initEdge(Edge*cur,Node* tail,Node* top,int weight){
    cur->weight = weight;
    cur->next = NULL;
    cur->tail = tail;
    cur->top = top;
}
void remoteNode(Node* tail,Node* top,int weight){
    Edge* cur = tail->firstEdge;
    if (cur == NULL){
        cur = newEdge;
        initEdge(cur,tail,top,weight);
        tail->firstEdge = cur;
        return;
    }
    while(cur->next!= NULL){
        cur = cur->next;
    }
    Edge* temp = newEdge;
    initEdge(temp,tail,top,weight);
    cur->next = temp;
    // 无向图第二次连接
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
Node* pushSequenceNode(Node* head,Node* sign){
    if (NodeNum <= 1){
        sign->sequenceNext = head->sequenceNext;
        *head = *sign;
        return head;
    }
    head->sequenceNext[NodeNum-2] = sign;
    return head;
}
void InsertNode(Node* root,Node* sign){
    if (root->ID >= sign->ID){
        if(root->left == NULL){
            root->left = sign;
            return;
        }
        InsertNode(root->left,sign);
    }else{
        if(root->right == NULL){
            root->right = sign;
            return;
        }
        InsertNode(root->right,sign);
    }
};
Node* searchNodeWithID(const Node* root,int ID){
    if (root == NULL || root->ID == ID){
        return root;
    }
    if(ID > root->ID){
        return searchNodeWithID(root->right,ID);
    }else{
        return searchNodeWithID(root->left,ID);
    }
};

Node* searchNodeWithName(const Node* root,char* name){
    Node *p = preOrderTrailTree(root,name);
    return p;
};

void setName(Node* root,char* name){
    strcpy(root->name,name);
};

void setIntroduce(Node* root,char* introduce){
    strcpy(root->introduce,introduce);
};
void setID(Node* root,int ID){
    root->ID = ID;
}
