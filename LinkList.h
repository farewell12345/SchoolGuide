//
// Created by tangz on 2020/9/25.
//

#ifndef PACKAG_LINKLIST_H
#define PACKAG_LINKLIST_H
#include <cstdio>
#include <cstdlib>

//数据定义
typedef char* dataType;

//结构体
typedef struct LinkList {
    char* data;
    struct LinkList *next;

} List;

//初始化
List *init() {
    return NULL;
}

//是否为空
int isEmpty(List *head) {
    return (!head) ? 0 : 1;
}

//输出
void display(List *head) {
    if (!isEmpty(head)) {
        printf("空的！\n Is Empty!");
        return;
    }
    List *p = head;
    while (p) {
        printf("%s", p->data);
        p = p->next;
    }
    printf("\n");
}

//查找
List *find(List *head, int location) {
    if (!isEmpty(head)) {
        printf("空的！\n Is Empty!");
        return NULL;
    }
    if (location < 1)
        return NULL;
    List *p = head;
    int j = 1;
    while (p && j != location) {
        p = p->next;
        ++j;
    }
    return p;
}

//添加
List *insert(List *head, int location, dataType i) {
    List *p, *q;
    q = find(head, location);
    if (!q && location >= 1) {
        printf("找不到你想插入的位置。\nLocation Not Found\n");
    }
    p = (List *) malloc(sizeof(List));
    p->data = i;
    if (location == 0) {
        p->next = head;
        head = p;
    } else {
        p->next = q->next;
        q->next = p;
    }
    return head;
}

//尾部添加
List *push(List *head, dataType i) {
    if (head == NULL) {
        head = (List *) malloc(sizeof(List));
        head->data = i;
        head->next = NULL;
        return head;
    }
    List *p = head;
    while (p->next) {
        p = p->next;
    }
    List *q = (List *) malloc(sizeof(List));
    q->next = NULL;
    q->data = i;
    p->next = q;
    return head;
}

//删除
List *deletes(List *head, dataType i) {
    List *p, *q = NULL;
    if (!isEmpty(head)) {
        printf("空的！\n Is Empty!");
        return head;
    }
    p = head;
    while (p && p->data != i) {
        q = p;
        p = p->next;
    }
    if (p) {
        if (!q)
            head = head->next;
        else
            q->next = p->next;
        free(p);
    }
    return head;
}

//3.2
void Num(List *head) {
    if (!isEmpty(head)) {
        printf("空的！\n Is Empty!");
        return;
    }
    List *p = head;
    int i = 0;
    while (p) {
        ++i;
        p = p->next;
    }
    printf("一共有%d个结点\nTotal Node has %d", i, i);
}

//3.5
/*
 * return
 * -2 链表为空
 * -1 无序
 *  1 有序
 */
#endif //PACKAG_LINKLIST_H
