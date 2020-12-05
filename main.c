#include <stdio.h>
#include "DTO/Initmap.h"
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
int NodeNum = 0;
int main(){
    Node *head = NULL;
    head = readExcel();
    frontOrderTrailTree(head);
    head = readRemote(head);
    Floyd(head);
    printf("最短路径模型计算完毕");
    while(1) {
        printf("\n1.All secene\n"
               "2.A to B shortest road\n"
               "0. exit");
        int i = 0;
        scanf("%d",&i);
        if (i == 0){
            break;
        }
        char *star = malloc(200),*end = malloc(200);
        switch(i){
            case 0:
                break;
            case 1:
                printMap(head);
                break;
            case 2:
                scanf("%s",star);
                scanf("%s",end);
                Node *startAddress = searchNodeWithName(head, star);
                Node *endAddress = searchNodeWithName(head, end);
                if (endAddress != NULL && startAddress != NULL) {
                    printf("\n%s->%s的最短路径为：\n",star,end);
                    printShortPath(head, startAddress, endAddress);
                } else {
                    printf("输入有误\n");
                }
                break;
            default:
                break;
        }

    }
    return 0;
}