//
// Created by Administrator on 2020/12/2.
//

#ifndef CLASS_PROTECT_TOOLSFUNCTION_H
#define CLASS_PROTECT_TOOLSFUNCTION_H
#include "../DTO/DTO.h"
#include "../DTO/Stack/Stack.h"
#include <cstdio>
int is_number(char * s);
void getPath(Stack* stack,const Node *head,int start,int end);
void freeStack(Stack *head);
Node *getNode(const Node *head, int i);
void Floyd(Node *head);
Stack * createShortedMap(Node** root,const int);
int getShortPath(Node* star,Node* end);
#endif //CLASS_PROTECT_TOOLSFUNCTION_H
