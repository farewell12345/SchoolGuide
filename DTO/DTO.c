//
// Created by Administrator on 2020/12/17.
//

//
// Created by Administrator on 2020/12/17.
//
#include "DTO.h"
/*创建栈*/
Stack *createStack(){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->top = NULL;
    return p;
};
/*压栈*/
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
    stackNode *p = head->top;
    head->top = head->top->next;
    p->next = NULL;
    return p;
}
/*获取栈顶元素，不弹栈*/
stackNode *getTopStack(Stack*head){
    return head->top;
}
/*初始化栈元素（封装结点）*/
stackNode *initStackNode(Node*p){
    stackNode *q =(stackNode*) malloc(sizeof(stackNode));
    q->data = p;
    q->next=NULL;
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
        if(t->data->ID == p->ID){
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
/*获取结点的出度*/
int getNodeSize(Node *star){
    int num = 0;
    Edge *p = star->firstEdge;
    while(p!=NULL){
        ++num;
        p = p->next;
    }
    return num;
}
/*深搜寻找两点之间的所有路径*/
void DFS(Stack* stack,Node* star,Node *end){
    if (star->ID == end->ID){
        printStack(stack);
        popStack(stack);
        return;
    }
    Edge* p = star->firstEdge;
    bool *rootVisited = malloc(sizeof(bool)*NodeNum);
    if(getNodeSize(star) == 0){
        popStack(stack);
        return;
    }
    for (int i = 0; i < NodeNum; ++i) {
        rootVisited[i] = false;
    }
    rootVisited[star->mainId] = true;
    for (int i = 0; i < getNodeSize(star); ++i,p=p->next) {
        if(rootVisited[p->top->mainId] == false && !NodeInStack(stack,p->top)){
            rootVisited[p->top->mainId] = true;
            pushStack(stack,initStackNode(p->top));
            DFS(stack,p->top,end);
        }
    }
    popStack(stack);
}
/*输出两点之间的所有路径*/
void printAllPath(Node *star,Node* end){
    if(star == NULL || end == NULL){
        printf("含有未知地点，请检查输入\n");
        return;
    }
    Stack* root = createStack();
    pushStack(root,initStackNode(star));
    Edge* p = star->firstEdge;
    bool *rootVisited = malloc(sizeof(bool)*NodeNum);
    for (int i = 0; i < NodeNum; ++i) {
        rootVisited[i] = false;
    }
    rootVisited[star->mainId-1] = true;
    for (int i = 0; i < getNodeSize(star); ++i,p=p->next) {
        if(rootVisited[p->top->mainId] == false && !NodeInStack(root,p->top)){
            rootVisited[p->top->mainId] = true;
            pushStack(root,initStackNode(p->top));
            DFS(root,p->top,end);
        }
    }
}