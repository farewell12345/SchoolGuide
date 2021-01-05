//
// Created by Administrator on 2021/1/5.
//

#ifndef CLASS_PROTECT_TREE_H
#define CLASS_PROTECT_TREE_H
#include "../DTO.h"
bool equals(char* name1,char* name2);
Node * frontOrderTrailTree(Node *head);
Node *preOrderTrailTree(const Node *head,char *name);
void InsertNode(Node* root, Node* sign);
Node* searchNodeWithID(const Node* root,int ID);
/*根据名字搜索结点*/
Node* searchNodeWithName(const Node* root,char* name);
#endif //CLASS_PROTECT_TREE_H
