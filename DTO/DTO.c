//
// Created by Administrator on 2020/12/17.
//

//
// Created by Administrator on 2020/12/17.
//
#include "DTO.h"
Stack *createStack(){
    Stack *p = (Stack*)malloc(sizeof(Stack));
    p->top = NULL;
    return p;
};
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
stackNode *popStack(Stack*head){
    stackNode *p = head->top;
    head->top = head->top->next;
    p->next = NULL;
    return p;
}
stackNode *getTopStack(Stack*head){
    return head->top;
}

stackNode *initStackNode(Node*p){
    stackNode *q =(stackNode*) malloc(sizeof(stackNode));
    q->data = p;
    q->next=NULL;
    return q;
}
bool StackIsEmpty(Stack*head){
    return head->top==NULL;
}
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
void printStack(Stack*head){
    stackNode * t = head->top;
    Stack *temp = createStack();
    while (t!=NULL){
        pushStack(temp,initStackNode(t->data));
        t = t->next;
    }
    while(!StackIsEmpty(temp)){
        printf("%s->",p->data->name);
    }
    printf("\n");
}
int getNodeSize(Node *star){
    int num = 0;
    Edge *p = star->firstEdge;
    while(p!=NULL){
        ++num;
        p = p->next;
    }
    return num;
}

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