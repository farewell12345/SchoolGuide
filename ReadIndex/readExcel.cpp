//
// Created by Administrator on 2020/12/3.
//
#include "readExcel.h"
#include "../List/LinkList.h"
/*�ִ��㷨*/
List* split(char* tab){
    char* parent = (char*)malloc(200);
    strcpy(parent,tab);
    List* head = NULL;
    char* token = strtok(parent,",");
    while(token!=NULL){
        List* p = init();
        p->next = NULL;
        p->data = (char*)malloc(sizeof(char)*200);
        strcpy(p->data,token);
        head = push(head,p);
        token = strtok(NULL, ",");
    }
    return head;
}
/*��ȡ������*/
int getLines(int type){
    FILE*fp;
    if(type==0)
        fp = fopen(PATH,"r");
    else
        fp = fopen(REMOTEPATH,"r");
    int c = 0,line = 0;
    while((c=fgetc(fp))!=EOF){
        if(c == '\n'){
            line++;
        }
    }
    fclose(fp);
    return line;
}
/*��ȡ������Ϣ*/
Node* readExcel() {
    Node* head = NULL;
    int line = getLines(0);
    FILE* fp = fopen(PATH,"r");     // fpָ���ļ�ͷ��
    fgetc(fp);
    char*** table = (char***)malloc(sizeof(char**)*line);
    for (int i = 0; i < line; ++i) {
        table[i] = (char**)malloc(sizeof(char*)*5);
        for (int j = 0; j < 5; ++j) {
            table[i][j] = (char*)malloc(sizeof(char)*200);
        }
    }
    int readLines = 0;
    while (!feof(fp)){
        char tables[200];
        fscanf(fp, "%s", tables);
        fgetc(fp);
        List* list = split(tables);
        for (int i = 0; i < 5; ++i) {
            strcpy(table[readLines][i],list->data);
            list = list->next;
        }
        readLines++;
    }
    fclose(fp);
    Node **tNode =(Node**)malloc(sizeof(Node*)*line);
    for (int i = 0; i < line; ++i) {
        tNode[i] =(Node*) malloc(sizeof(Node));
    }
    for (int i = 0; i < line; ++i) {
        tNode[i] = initNode(tNode[i]);
        setName(tNode[i],table[i][0]);
        setID(tNode[i],atoi(table[i][1]));
        setIntroduce(tNode[i],table[i][2]);
        tNode[i]->x = atoi(table[i][3]);
        tNode[i]->y = atoi(table[i][4]);
        tNode[i]->mainId = NodeNum;
        if (head == NULL){
            head = tNode[i];
            continue;
        }
        InsertNode(head,tNode[i]);
    }
    head->sequenceNext = NULL;
    head->sequenceNext = tNode;
    return head;
}
/*��ȡ������Ϣ*/
Node* readRemote(Node* head){
    int line = getLines(1);
    FILE* fp = fopen(REMOTEPATH,"r");
    fgetc(fp);
    char*** table = (char***)malloc(sizeof(char**)*line);
    for (int i = 0; i < line; ++i) {
        table[i] = (char**)malloc(sizeof(char*)*3);
        for (int j = 0; j < 3; ++j) {
            table[i][j] = (char*)malloc(sizeof(char)*50);
        }
    }
    int readLines = 0;
    while (!feof(fp)){
        char* tables =(char*) malloc(sizeof(char)*200);
        fscanf(fp, "%s", tables);

        fgetc(fp);
        List* list = split(tables);
        for (int i = 0; i < 3; ++i) {
            strcpy(table[readLines][i],list->data);
            list = list->next;
        }
        readLines++;
        free(tables);
    }
    for (int i = 0; i < line; ++i) {
        Node* star = searchNodeWithName(head,table[i][0]);
        int weight = atoi(table[i][1]);
        Node* end = searchNodeWithName(head,table[i][2]);
        remoteNode(star,end,weight);
    }
    return head;
}