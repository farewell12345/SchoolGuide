//
// Created by Administrator on 2021/1/5.
//

#ifndef CLASS_PROTECT_STACK_H
#define CLASS_PROTECT_STACK_H
#include "../DTO.h"
#include <string.h>
typedef struct stack{
    Node *data;
    struct stack* next;
}stackNode;

typedef struct{
    struct stack* top;
}Stack;
Stack *createStack();
Stack* pushStack(Stack*head,stackNode *p);
Stack* reverseStack(Stack* p);
stackNode *popStack(Stack*head);
stackNode *getTopStack(const Stack*head);
stackNode *initStackNode(Node*p);
bool StackIsEmpty(Stack*head);
bool NodeInStack(Stack* head,Node* p);
bool StackIsFull(Stack* head,int MAXSIZE);
void printStack(Stack*head);
int getStackSize(Stack *t);
#endif //CLASS_PROTECT_STACK_H
