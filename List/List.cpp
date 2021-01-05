//
// Created by Administrator on 2021/1/5.
//
#include "LinkList.h"

//初始化
List *init() {
    return (List*)malloc(sizeof(List));
}
//尾部添加
List *ListPush(List *head, List* i) {
    if (head == NULL) {
        head = i;
        return head;
    }
    List *p = head;
    while (p->next!=NULL) {
        p = p->next;
    }
    p->next = i;
    p->next->next = NULL;
    return head;
}