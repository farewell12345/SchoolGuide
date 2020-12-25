//
// Created by Administrator on 2020/12/2.
//
/*������������*/
#include "toolsFunction.h"
#include <cstring>
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9') // �궨���ж�һ���ַ��ǲ�������

int abs(int c){
    return c<0? c*-1:c;
}

// ȫ�ֵĽ����
extern int **shortPath; // ������������
extern int **path; // ·����������
Node *visited[23]; // ���ʱ��
int visitedNum = 0; // �ѷ��ʵ�����
/* �ж��ַ����Ƿ�Ϊ��*/
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
/*�жϽ���Ƿ񱻷��ʹ�*/
bool NodeIsVisited(Node* Nodes){
    for (int i = 0; i < visitedNum; ++i) {
        if (visited[i]==Nodes){
            return true;
        }
    }
    return false;
}
/* ��ȡ�����������֮��ľ��룬����������ͷ���INF��INTMAX��*/
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
/*����·��������ȡ����֮������·�������*/
void getPath(Stack* stack,const Node *head,int start,int end){ // �ݹ������··��
    if (start == path[start][end]){ // �˴�˵���ص�����㣬������ݹ飬����㿪ʼ���·��
        pushStack(stack,initStackNode(getNode(head,start)));
        pushStack(stack,initStackNode(getNode(head,end)));
    }else{
        getPath(stack,head,start,path[start][end]); // һֱ��������ȥ
        pushStack(stack,initStackNode(getNode(head,end)));
    }
}
// ���Ѵ�ӡ������Ϣ��
void dfs(Node* cur) {
    if (NodeIsVisited(cur) == true) return;
    visited[visitedNum-1] = cur;
    visitedNum++;
    Edge *edge = cur->firstEdge;
    while (edge != NULL) {
        if(NodeIsVisited(edge->top) == false) {
            printf("%s", edge->top->name);
            for (int i = 0; i < (20-strlen(edge->top->name)); ++i) {
                printf(" ");
            }
            printf("|\tID:%d\t|\n",edge->top->ID);
            dfs(edge->top);
        }
        edge = edge->next;
    }
}
/*����������ȡ���*/
Node *getNode(const Node *head, int i){
    return head->sequenceNext[i];
};
/*�ж������ַ����Ƿ���ͬ*/
bool equals(char* name1,char* name2){
    return strcmp(name1,name2) == 0? true:false;
};
/*������*/
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
    Node* cur =(Node*) head;
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
/*��ӡ�����*/
void printMap(const Node *head){
    for (int i = 0; i < NodeNum; ++i) {
        printf("%s", head->sequenceNext[i]->name);
        for (int j = 0; j < abs(20-strlen(head->sequenceNext[i]->name)); ++j) {
            printf(" ");
        }
        printf("|\tID:%d\t|\n",head->sequenceNext[i]->ID);
    }
};
/*��Դ���·���㷨*/
void Floyd(Node* head) {
    /*����ռ�*/
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
/*���������·�����*/
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
    Stack *temp  = createStack();
    getPath(temp, head,i,j); // ���i�㵽j���·��
    printStack(temp);
    printf("\n");
    freeStack(temp);
};
void freeStack(Stack *head){
    if (head == nullptr)return;
    if (getTopStack(head) == NULL){
        return;
    }
    stackNode * p= popStack(head);
    while (p!=nullptr){
        if(getTopStack(head)!=nullptr) {
            p = popStack(head);
        }else{
            break;
        }
    }
}
/*��ȡ���������·�����ȣ�������Floyd�Ժ�*/
int getShortPath(Node* star,Node* end){
    return shortPath[star->mainId-1][end->mainId-1];
}
bool NodeArrayIsEmpty(Node** root,int NodeSize){
    for (int i = 0; i < NodeSize; ++i) {
        if (root[i]!=nullptr){
            return false;
        }
    }
    return true;
}
/*;�����������·������*/
Stack * createShortedMap(Node** root,int NodeSize){
    Stack* vector = createStack();
    Node *now = root[0];
    int min = -1;
    pushStack(vector,initStackNode(now));
    while (!StackIsFull(vector,NodeSize)){
        for (int i = 0; i < NodeSize; ++i) {
            if (NodeInStack(vector,root[i])){
                continue;
            }
            if(min == -1){
                min = i;
                continue;
            }
            if(getShortPath(now,root[min]) < getShortPath(now,root[i])){
                min = i;
            }
        }
        if(min == -1){
            break;
        }
        pushStack(vector,initStackNode(root[min]));
        now = root[min];
        min = -1;
    }
    return vector;
}