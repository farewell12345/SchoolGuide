//
// Created by Administrator on 2020/12/2.
//
/*������������*/
#include "toolsFunction.h"
#include <string.h>
#include <math.h>

#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
extern NodeNum;
extern int **shortPath;
extern int **path;
Node *visited[23];
int visitedNum = 0;
/* Whether string s is a number.
   Returns 0 for non-number, 1 for integer, 2 for hex-integer, 3 for float */
int is_number(char * s)
{
    bool flag = true;
    for (int i = 0; i < strlen(s); ++i) {
        if(!IS_DIGIT(s[i])){
            flag = false;
        }
    }
    return flag;
}
bool NodeIsVisited(Node* Nodes){
    for (int i = 0; i < visitedNum; ++i) {
        if (visited[i]==Nodes){
            return true;
        }
    }
    return false;
}
int getWeight(Node* tail,Node* top){
    Edge *e = tail->firstEdge;
    while(e!=NULL){
        if (e->top == top){
            return e->weight;
        }
        e = e->next;
    }
    return INF;
}
void getPath(const Node *head,int start,int end){ // �ݹ������··��
    if (start == path[start][end]){ // �˴�˵���ص�����㣬������ݹ飬����㿪ʼ���·��
        printf("%s->%s->",getNode(head,start)->name,getNode(head,end)->name);
    }else{
        getPath(head,start,path[start][end]); // һֱ��������ȥ
        printf("%s->",getNode(head,end)->name);
    }
}
void dfs(Node* cur) {
    if (NodeIsVisited(cur) == true) return;
    visited[visitedNum-1] = cur;
    visitedNum++;
    Edge *edge = cur->firstEdge;
    while (edge != NULL) {
        if(NodeIsVisited(edge->top) == false) {
            printf("%s", edge->top->name);
            for (int i = 0; i < abs(20-strlen(edge->top->name)); ++i) {
                printf(" ");
            }
            printf("|\tID:%d\t|\n",edge->top->ID);
            dfs(edge->top);
        }
        edge = edge->next;
    }
}
Node *getNode(const Node *head, int i){
    return head->sequenceNext[i];
};
bool equals(char* name1,char* name2){
    return strcmp(name1,name2) == 0? true:false;
};
Node *prev; // �ϴη��ʵĽڵ�(ǰ���ڵ㣩
Node * frontOrderTrailTree(Node *head){
    if(head == NULL) return head;

    if(head->left == NULL){ // ��ѭ��ǰ�Һ�
        head->left = prev; // �����е���ڵ�ָ��ǰ���ڵ�
        head->leftTag = 1; // ��ʾ����ڵ����ָ���ѱ�������
    }
    if(prev != NULL && prev->right == NULL){
        prev->right = head; // �����е��ҽڵ�ָ���̽ڵ�
        prev ->rightTag = 1;// ��ʾ����ڵ����ָ���ѱ�������
    }

    prev = head; // ��������prev�ƶ���������ʼѰ��head����һ����̽ڵ�
    if(head->leftTag == 0){ // �жϵ�ǰ�ڵ����ڵ���û����������
        head->left = frontOrderTrailTree(head->left);// ��Ѱ������
    }
    if(head->rightTag == 0){
        head->right = frontOrderTrailTree(head->right); // ��Ѱ������
    }
    return head;
}
/*��������*/
Node *preOrderTrailTree(const Node *head,char *name){
    Node* cur = head;
    /*�������Žڵ����±�����ֱ�����нڵ�ȫ��������
     * �������Ժ��������һ���ڵ���Һ��ӣ���̽ڵ㣩ΪNULL*/
    while (cur!=NULL)
    {
        while (cur->leftTag == 0)
        {
            if (equals(name,cur->name)){
                return cur;
            }
            cur = cur->left; // �����������±���ֱ���ײ�
        }
        if (equals(name,cur->name)){
            return cur;
        }
        cur = cur->right; // �����Һ���Ѱ�Һ�̽ڵ�
    }
    return NULL;
}
void printMap(const Node *head){
    for (int i = 0; i < NodeNum; ++i) {
        printf("%s", head->sequenceNext[i]->name);
        for (int j = 0; j < abs(20-strlen(head->sequenceNext[i]->name)); ++j) {
            printf(" ");
        }
        printf("|\tID:%d\t|\n",head->sequenceNext[i]->ID);
    }
};
void Floyd(Node* head) {
    shortPath = (int **) malloc(sizeof(int *) * NodeNum);
    path = (int **) malloc(sizeof(int *) * NodeNum);
    for (int i = 0; i < NodeNum; ++i) {
        shortPath[i] = (int *) malloc(sizeof(int)*NodeNum);
        path[i] = (int *) malloc(sizeof(int)*NodeNum);
    }
    for (int i = 0; i < NodeNum; ++i) {
        for (int j = 0; j < NodeNum; ++j) {
            if (i == j) {
                shortPath[i][j] = 0; // ���㵽����ľ��� = 0
            } else {
                shortPath[i][j] = getWeight(getNode(head, i), getNode(head, j)); // ��i�㵽j��ľ���Ȩֵ��������
            }
            path[i][j] = i; // ��ʱi->j���� i
        }
    }

    int temp;
    for (int k = 0; k < NodeNum; ++k) { // �м��
        // �̶�KΪ�м�·���㣬�鿴i��k��j��k�ܷ��γ�ͨ·�������γ�ͨ·���ٰ�·����С��k�������ʱ����
        for (int i = 0; i < NodeNum; ++i) {
            for (int j = 0; j < NodeNum; ++j) {
                temp = (shortPath[i][k] == INF || shortPath[k][j] == INF) ? INF : (shortPath[i][k] + shortPath[k][j]); // �ж�
                if (shortPath[i][j] > temp) { // ���temp��ԭ��·���̾��滻
                    shortPath[i][j] = temp;
                    path[i][j] = path[k][j]; // ��K�����·��
                }
            }
        }
    }
}
void printShortPath(const Node*head,Node* star,Node* end){
    int i = star->mainId-1,j = end ->mainId-1;
    if (shortPath[i][j] < INF) {
        printf("%s->",star->name);
        printf("%s",end->name);
        printf(":%dM\n·��: ", shortPath[i][j]); // ��ȡi�㵽j������·��
    }else {
        printf("������ʱ�޷�ֱ�ӵ���");
        return;
    }
    getPath(head,i,j); // ���i�㵽j���·��
    printf("\n");
};
int getShortPath(Node* star,Node* end){
    return shortPath[star->mainId-1][end->mainId-1];
}
Stack * createShortedMap(Node** root,int NodeSize){
    Stack* vector = createStack();
    pushStack(vector,initStackNode(root[0]));
    printf("����%d�ڵ�\n",NodeSize);
    while(!StackIsFull(vector,NodeSize)){
        stackNode * top = getTopStack(vector);
        Node * min = root[1];
        for (int j = 1; j < NodeSize; ++j) {
            if (!NodeInStack(vector,root[j])){
                if(min == NULL){
                    min = root[j];
                    continue;
                }
                if(getShortPath(top->data,root[j]) < getShortPath(top->data,min)){
                    min = root[j];
                }
            }
        }
        pushStack(vector,initStackNode(min));
    }
    pushStack(vector,initStackNode(root[NodeSize]));
    return reverseStack(vector);
}