//
// Created by tangz on 2020/9/25.
//

#ifndef PACKAG_LINKLIST_H
#define PACKAG_LINKLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//�ṹ��
typedef struct List {
    char *data;
    struct List *next;
} List;

//��ʼ��
List *init();
//β�����
List *ListPush(List *head, List* i);
#endif //PACKAG_LINKLIST_H