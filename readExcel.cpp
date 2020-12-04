//
// Created by Administrator on 2020/12/3.
//
#include "readExcel.h"
#include "Initmap.h"
#include <cstring>
#include "LinkList.h"
#include "toolsFunction.h"

List* split(char* parent){
    List* head = init();
    char* temp = strtok(parent,",");
    while(temp!=nullptr){
        head = push(head,temp);
        temp = strtok(nullptr,",");
    }
    return head;
}

void readExcel(node* head) {
    FILE* fp = fopen(PATH,"r");     // fp指向文件头部
    char table[1000];
    fscanf(fp, "%s", table);
    fgetc(fp);
    while (!feof(fp)){
        char table[1000];
        fscanf(fp, "%s", table);
        fgetc(fp);
        printf("%s\n",table);
        List* list = split(table);
        node* t = initNode();
        setName(t,list->data);
        list = list->next;
        setID(t,atoi(list->data));
        list = list->next;
        setIntroduce(t,list->data);
        list = list->next;
        t->x = atof(list->data);
        list = list->next;
        t->y = atof(list->data);
        InsertNode(head,t);
        pushSequenceNode(head,t);
        printf("\n");
    }
    fclose(fp);
}
