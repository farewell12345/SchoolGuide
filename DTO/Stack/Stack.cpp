//
// Created by Administrator on 2021/1/5.
//
#include "Stack.h"
/*创建栈*/
Stack *createStack(){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->top = NULL;
    return p;
};
/*压栈*/
bool stackNodeIsInStack(Stack* head,stackNode* node){
    stackNode* p = head->top;
    while(p!=NULL){
        if (p->data->ID == node->data->ID){
            return true;
        }
        p = p->next;
    }
    return false;
}
Stack* pushStack(Stack* head,stackNode* node){
    stackNode *p = node;
    if(head->top == NULL){
        head->top = p;
        head->top->next = NULL;
    }else{
        p->next = head->top;
        head->top = p;
    }
    return head;
}
/*弹栈*/
stackNode *popStack(Stack*head){
    if (head == NULL)return NULL;
    stackNode *p = head->top;
    head->top = head->top->next;
    p->next = NULL;
    return p;
}
/*获取栈顶元素，不弹栈*/
stackNode *getTopStack(const Stack*head){
    return head->top;
}
/*初始化栈元素（封装结点）*/
stackNode *initStackNode(Node*p){
    stackNode *q =(stackNode*) malloc(sizeof(stackNode));
    q->data = p;
    q->next= nullptr;
    return q;
}
/*栈判空*/
bool StackIsEmpty(Stack*head){
    return head->top==NULL?true:false;
}
/*判断结点是否在栈里*/
bool NodeInStack(Stack* head,Node* p){
    stackNode * t = head->top;
    while (t!=NULL){
        if(t->data->ID == p->ID || strcmp(t->data->name,p->name) == 0){
            return true;
        }
        t = t->next;
    }
    return false;
}
/*判断栈是否满*/
bool StackIsFull(Stack* head,int MAXSIZE){
    stackNode*p = getTopStack(head);
    int num = 0;
    while(p!=NULL){
        num++;
        p = p->next;
    }
    return num>=MAXSIZE;
}
/*反转栈*/
Stack* reverseStack(Stack* p){
    Stack *temp = createStack();
    while(!StackIsEmpty(p)){
        pushStack(temp,popStack(p));
    }
    free(p);
    return temp;
}
int getStackSize(Stack *t){
    int num = 0;
    stackNode *temp = getTopStack(t);
    while (temp!=NULL){
        ++num;
        temp = temp->next;
    }
    return num;
}
/*打印整个栈（不作任何操作）*/
void printStack(Stack*head){
    stackNode * t = head->top;
    Stack *temp = createStack();
    while (t!=NULL){
        pushStack(temp,initStackNode(t->data));
        t = t->next;
    }
    while(!StackIsEmpty(temp)){
        stackNode* p = popStack(temp);
        printf("%s->",p->data->name);
        free(p);
    }
    printf("\n");
}
