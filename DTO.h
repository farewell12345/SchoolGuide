//
// Created by Administrator on 2020/12/2.
//
#pragma once
#ifndef CLASS_PROTECT_DTO_H
#define CLASS_PROTECT_DTO_H
#include <malloc.h>
#include <climits>
#define PATH "F://Program//Clion-Protect//class_protect//place.csv"
#define newNode (Node*)malloc(sizeof(Node))
#define newEdge (Edge*)malloc(sizeof(Edge))
#define bool int
#define true 1
#define false 0
#define INF INT_MAX
struct node;
struct edge;
extern int nodeNum;
typedef struct edge{
      int weight;
      node* top,*tail; // 定义弧头，弧尾的顶点
      edge * next;
}Edge;

typedef struct node{
    int mainId; // 快速索引ID
    char* name; // 景点名称
    int ID; // 代号
    char* introduce; // 介绍
    double x,y; // 在窗口中的坐标

    Edge* firstEdge; // 邻接表首边
    node* left; // 根据ID序号构建二叉排序树
    int leftTag;
    node* right;
    int rightTag;

    node* sequenceNext; // 顺序下一个
}Node;
#endif //CLASS_PROTECT_DTO_H
