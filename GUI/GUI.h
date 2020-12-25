//
// Created by Administrator on 2020/12/22.
//

#ifndef CLASS_PROTECT_GUI_H
#define CLASS_PROTECT_GUI_H
#include <graphics.h>//包含EGE的头文件
#include "../DTO/DTO.h"
void initWindows(Node *head);
void FlushModeBehave(char mode[]);
void FlushMap(Node* head);
void drawMenu();
void drawTable(Node *head);
void drawBackGround();
void DrawOk();
void Guide(Node*head,Node* nowNode);
void DrawTwoNodeShortPath(char* path,Node* head,Node*start,Node*end);
void TwoNodeAllPath(Node* head,Node *star,Node* end);
void clear(Node* head);
#endif //CLASS_PROTECT_GUI_H
