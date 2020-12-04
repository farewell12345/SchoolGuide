//
// Created by Administrator on 2020/12/2.
//
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef CLASS_PROTECT_DTO_H
#define CLASS_PROTECT_DTO_H
#include <malloc.h>
#include <limits.h>
#include "../config.h"
#define newEdge (Edge*)malloc(sizeof(Edge))
#define bool int
#define true 1
#define false 0
#define INF INT_MAX
struct Node;
struct Edge;
extern int NodeNum;
typedef struct Edge{
      int weight;
      struct Node* top,*tail; // 定义弧头，弧尾的顶点
      struct Edge * next;
}Edge;

typedef struct Node{
    int mainId; // 快速索引ID
    char name[50]; // 景点名称
    int ID; // 代号
    char introduce[200]; // 介绍
    double x,y; // 在窗口中的坐标
    Edge* firstEdge; // 邻接表首边
    struct Node* left; // 根据ID序号构建二叉排序树
    int leftTag;
    struct Node* right;
    int rightTag;
    struct Node* sequenceNext; // 顺序下一个
}Node;
#endif //CLASS_PROTECT_DTO_H
