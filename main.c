/***C语言校园导游系统
 * 【问题描述】
    设计一个校园导游程序，为来访的客人提供各种信息查询服务。
  【基本要求】
   设计中北大学的校园平面图，所含景点不少于10个，以图中顶点表示校内各景点，存放景点名称、代号、简介等信息；以边表示路径，存放路径长度等相关信息。
   为来访客人提供图中任意景点相关信息的查询。
   为来访客人提供图中任意景点的问路查询，即查询任意两相景点之间的一条最短的简单路径。
  求校园图的关节点(待实现）
  提供图中任意景点问路查询，即求任意两个景点之间的所有路径。（待实现）
  提供校园图中多个景点的最佳访问路线查询，即求途经这多个景点的最佳路径。（待实现）
 * author：陈昊（https://github.com/farewell12345)、冀鹏宇、李照熙
 * 功能：
 *   1. 向csv中手动录入数据，解析csv中的数据（csv解析算法）
 *   2. 计算整张图中各点之间的最短路径（Floyd算法）
 *   3. 输入所处位置和目的地，输出两点之间的最短路径（Floyd算法解析路径向量和距离向量）
 *   4. 输出对应景点的信息（前序线索二叉搜索树）
 * 本项目所属仓库：
 *   https://github.com/farewell12345/SchoolGuide
 * **/
#include <stdlib.h>
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
               "2.查询某个景点\n"
               "3.途径多个景点的最佳路径\n"
               "4.两个景点之间的所有路径\n"
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
            case 3:
                printf("输入起点:\n");
                scanf("%s",star);
                printf("输入终点:\n");
                scanf("%s",end);
                printf("输入途径景点,输入-1结束\n");
                Node** passingNode = malloc(sizeof(Node*)*NodeNum);
                startAddress = searchNodeWithName(head,star);
                endAddress = searchNodeWithName(head,end);
                passingNode[0] = startAddress;
                int passingNum = 1;
                scanf("%s",temp_node);
                while (strcmp(temp_node,"-1") != 0){
                    temp = searchNodeWithName(head,temp_node);
                    if (temp != NULL){
                        passingNode[passingNum] = malloc(sizeof(Node));
                        passingNode[passingNum]->ID = temp->ID;
                        passingNode[passingNum++]->mainId = temp->mainId;
                    }else{
                        printf("没有找到这个结点，请重新输入\n");
                    }
                    scanf("%s", temp_node);
                }
                passingNode[passingNum] = endAddress;
                Stack * t = createShortedMap(passingNode,passingNum);
                while (StackIsEmpty(t) == false){
                    stackNode* now = popStack(t),*next = getTopStack(t);
                    startAddress = searchNodeWithID(head,now->data->ID);
                    endAddress = searchNodeWithID(head,next->data->ID);
                    printShortPath(head,startAddress,endAddress);
                    if(next->next == NULL){
                        break;
                    }
                }
                free(t);
                for (int j = 0; j < passingNum; ++j) {
                    free(passingNode[j]);
                }
                break;
            case 4:
                printf("输入起点:\n");
                scanf("%s",star);
                printf("输入终点:\n");
                scanf("%s",end);
                printAllPath(searchNodeWithName(head,star),searchNodeWithName(head,end));
                break;
        }
        printf("按任意键继续...");
        getchar();
        getchar();
    }
    return 0;
}