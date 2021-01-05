//
// Created by Administrator on 2020/12/2.
//
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef CLASS_PROTECT_DTO_H
#define CLASS_PROTECT_DTO_H
#include <malloc.h>
#include <climits>
#include <cstdio>
#include "../config.h"
#define newEdge (Edge*)malloc(sizeof(Edge))
#define bool int
#define true 1
#define false 0
#define INF INT_MAX //����֮�������
struct Node;
struct Edge;
extern int NodeNum;
typedef struct Edge{
      int weight;
      struct Node* top,*tail; // ���廡ͷ����β�Ķ���
      struct Edge * next;
}Edge;
typedef struct Node{
    int mainId; // ��������ID
    char name[50]; // ��������
    int ID; // ����
    char introduce[200]; // ����
    int x,y; // �ڴ����е�����
    Edge* firstEdge; // �ڽӱ��ױ�
    struct Node* left; // ����ID��Ź�������������
    int leftTag;
    struct Node* right;
    int rightTag;
    struct Node** sequenceNext; // ˳����һ��
}Node;
void printAllPath(Node *star,Node* end);
int getNodeSize(Node *star);
#endif //CLASS_PROTECT_DTO_H
