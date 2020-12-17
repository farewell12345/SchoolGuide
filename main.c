#include <stdio.h>
#include <stdlib.h>
#include "DTO/Initmap.h"
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
int NodeNum = 0;
int **shortPath = NULL;
int **path = NULL;
Node *head = NULL;
int main(){
    head = readExcel();
    frontOrderTrailTree(head);
    head = readRemote(head);
    Floyd(head);
    while(1) {
        printf("-----------------------------------\n");
        printMap(head);
        printf("-----------------------------------\n");
        printf("1.导航\n"
               "2.获取某个景点的介绍\n"
               "0. exit\n");
        int i = 0;
        scanf("%d",&i);
        if (i == 0){
            break;
        }
        char *star = malloc(200),*end = malloc(200),*temp_node = malloc(200);
        switch(i){
            case 0:
                break;
            case 1:
                printf("输入你所在的位置的名字或ID:\n");
                scanf("%s",star);
                printf("输入目标位置的名字或ID:\n");
                scanf("%s",end);
                Node *startAddress = searchNodeWithName(head, star);
                Node *endAddress = searchNodeWithName(head, end);
                startAddress = startAddress == NULL? searchNodeWithID(head,atoi(star)):startAddress;
                endAddress = endAddress == NULL? searchNodeWithID(head,atoi(end)):endAddress;
                if (endAddress != NULL && startAddress != NULL) {
                    printf("\n%s->%s的最短路径为：\n",startAddress->name,endAddress->name);
                    printShortPath(head, startAddress, endAddress);
                } else {
                    printf("输入有误\n");
                }
                break;
            case 2:
                printf("输入目标位置的名字或ID:\n");
                scanf("%s",temp_node);
                Node *temp = searchNodeWithName(head,temp_node);
                if (temp == NULL){
                    if (is_number(temp_node) == false) {
                        printf("不存在此地点\n");
                        break;
                    }
                    temp = searchNodeWithID(head,atoi(temp_node));
                    if (temp == NULL){
                        printf("不存在此地点\n");
                        break;
                    }
                }
                if (temp!=NULL){
                    printf("%s:%s\n",temp->name,temp->introduce);
                }
                break;
        }
        printf("按任意键继续...");
        getchar();
        getchar();
    }
    return 0;
}