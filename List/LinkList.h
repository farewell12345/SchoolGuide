//
// Created by tangz on 2020/9/25.
//

#ifndef PACKAG_LINKLIST_H
#define PACKAG_LINKLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//结构体
typedef struct List {
    char *data;
    struct List *next;
} List;

//初始化
List *init();
//尾部添加
List *ListPush(List *head, List* i);
#endif //PACKAG_LINKLIST_H