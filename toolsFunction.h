//
// Created by Administrator on 2020/12/2.
//

#ifndef CLASS_PROTECT_TOOLSFUNCTION_H
#define CLASS_PROTECT_TOOLSFUNCTION_H
#include "DTO.h"
#include <cstdio>
extern int nodeNum;
static int visitedNum = 0;
node *preOrderTrailTree(node *head,char *name);
bool equals(char* name1,char* name2);
node * frontOrderTrailTree(node *head);
void printMap(node *head);
node *getNode(node *head, int i);
void Floyd(node *head);
void printShortPath(node*head,node* star,node* end);
#endif //CLASS_PROTECT_TOOLSFUNCTION_H
