//
// Created by Administrator on 2020/12/2.
//

#ifndef CLASS_PROTECT_TOOLSFUNCTION_H
#define CLASS_PROTECT_TOOLSFUNCTION_H
#include "../DTO/DTO.h"
#include <stdio.h>
extern int NodeNum;

Node *preOrderTrailTree(Node *head,char *name);
bool equals(char* name1,char* name2);
Node * frontOrderTrailTree(Node *head);
void printMap(Node *head);
Node *getNode(Node *head, int i);
void Floyd(Node *head);
void printShortPath(Node* head,Node* star,Node* end);
#endif //CLASS_PROTECT_TOOLSFUNCTION_H
