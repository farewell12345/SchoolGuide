//
// Created by Administrator on 2020/12/2.
//

#ifndef CLASS_PROTECT_INITMAP_H
#define CLASS_PROTECT_INITMAP_H
#include "DTO.h"
extern int nodeNum;
Node* createMap();
Node* initNode();
void initEdge(Edge*cur,Node* tail,Node* top,int weight);
void pushSequenceNode(Node* head,Node* sign);
void InsertNode(Node* root,Node* sign);
void setName(Node* root,char* name);
void setIntroduce(Node* root,char* introduce);
void setID(Node* root,int ID);
Node* searchNodeWithID(Node* root,int ID);

Node* searchNodeWithName(Node* root,char* name);
void remoteNode(Node* tail,Node* top,int);
#endif //CLASS_PROTECT_INITMAP_H
