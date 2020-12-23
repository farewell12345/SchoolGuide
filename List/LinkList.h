//
// Created by tangz on 2020/9/25.
//

#ifndef PACKAG_LINKLIST_H
#define PACKAG_LINKLIST_H
#include <stdio.h>
#include <stdlib.h>
//���ݶ���
typedef char* dataType;


//�ṹ��
typedef struct List {
    char *data;
    struct List *next;
} List;

//��ʼ��
List *init() {
    return (List*)malloc(sizeof(List));
}

//�Ƿ�Ϊ��
int isEmpty(List *head) {
    return (!head) ? 0 : 1;
}

//���
void display(List *head) {
    if (!isEmpty(head)) {
        printf("�յģ�\n Is Empty!");
        return;
    }
    List *p = head;
    while (p) {
        printf("%s", p->data);
        p = p->next;
    }
    printf("\n");
}

//����
List *find(List *head, int location) {
    if (!isEmpty(head)) {
        printf("�յģ�\n Is Empty!");
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

//���
List *insert(List *head, int location, dataType i) {
    List *p, *q;
    q = find(head, location);
    if (!q && location >= 1) {
        printf("�Ҳ�����������λ�á�\nLocation Not Found\n");
    }
    p = (List *) malloc(sizeof(List));
    strcpy(p->data,i);
    if (location == 0) {
        p->next = head;
        head = p;
    } else {
        p->next = q->next;
        q->next = p;
    }
    return head;
}

//β�����
List *push(List *head, List* i) {
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

//ɾ��
List *deletes(List *head, dataType i) {
    List *p, *q = NULL;
    if (!isEmpty(head)) {
        printf("�յģ�\n Is Empty!");
        return head;
    }
    p = head;
    while (p && strcmp(p->data,i)!=0) {
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
        printf("�յģ�\n Is Empty!");
        return;
    }
    List *p = head;
    int i = 0;
    while (p) {
        ++i;
        p = p->next;
    }
    printf("һ����%d�����\nTotal Node has %d", i, i);
}

//3.5
/*
 * return
 * -2 ����Ϊ��
 * -1 ����
 *  1 ����
 */
#endif //PACKAG_LINKLIST_H