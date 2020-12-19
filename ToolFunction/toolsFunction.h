//
// Created by Administrator on 2020/12/2.
//

#ifndef CLASS_PROTECT_TOOLSFUNCTION_H
#define CLASS_PROTECT_TOOLSFUNCTION_H
#include "../DTO/DTO.h"
#include <stdio.h>
extern int NodeNum;

int is_number(char * s);
Node *preOrderTrailTree(const Node *head,char *name);
bool equals(char* name1,char* name2);
Node * frontOrderTrailTree(Node *head);
void printMap(const Node *head);
Node *getNode(const Node *head, int i);
void Floyd(Node *head);
Stack * createShortedMap(Node** root,int);
void printShortPath(const Node* head,Node* star,Node* end);
#endif //CLASS_PROTECT_TOOLSFUNCTION_H
