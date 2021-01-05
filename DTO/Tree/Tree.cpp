//
// Created by Administrator on 2021/1/5.
//
#include "Tree.h"
#include "string.h"
bool equals(char* name1,char* name2){
    return strcmp(name1,name2) == 0? true:false;
};
/*线索化*/
Node *prev; // 上次访问的节点(前驱节点）
Node * frontOrderTrailTree(Node *head){
    if(head == NULL) return head;

    if(head->left == NULL){ // 遵循左前右后
        head->left = prev; // 将空闲的左节点指向前驱节点
        head->leftTag = 1; // 表示这个节点的左指针已被线索化
    }
    if(prev != NULL && prev->right == NULL){
        prev->right = head; // 将空闲的右节点指向后继节点
        prev ->rightTag = 1;// 表示这个节点的右指针已被线索化
    }

    prev = head; // 线索化后将prev移动过来，开始寻找head的下一个后继节点
    if(head->leftTag == 0){ // 判断当前节点的左节点有没有线索化过
        head->left = frontOrderTrailTree(head->left);// 搜寻左子树
    }
    if(head->rightTag == 0){
        head->right = frontOrderTrailTree(head->right); // 搜寻右子树
    }
    return head;
}
/*遍历查找*/
Node * preOrderTrailTree(const Node *head,char *name){
    Node* cur =(Node*) head;
    /*不断沿着节点往下遍历，直到所有节点全部被遍历
     * 线索化以后，树的最后一个节点的右孩子（后继节点）为NULL*/
    while (cur!=NULL)
    {
        while (cur->leftTag == 0)
        {
            if (equals(name,cur->name)){
                return cur;
            }
            cur = cur->left; // 沿着左孩子向下遍历直到底部
        }
        if (equals(name,cur->name)){
            return cur;
        }
        cur = cur->right; // 沿着右孩子寻找后继节点
    }
    return NULL;
}
void InsertNode(Node* root,Node* sign){
    if (root->ID >= sign->ID){ // ID号大的在右，小的在左
        if(root->left == NULL){
            root->left = sign;
            return;
        }
        InsertNode(root->left,sign);
    }else{
        if(root->right == NULL){
            root->right = sign;
            return;
        }
        InsertNode(root->right,sign);
    }
}
/*根据ID搜索结点*/
Node* searchNodeWithID(const Node* root,int ID){
    if (root == NULL || root->ID == ID){
        return (Node*)root;
    }
    if(ID > root->ID){
        return searchNodeWithID(root->right,ID);
    }else{
        return searchNodeWithID(root->left,ID);
    }
};
/*根据名字搜索结点*/
Node* searchNodeWithName(const Node* root,char* name){
    Node *p = preOrderTrailTree(root,name);
    return p;
}