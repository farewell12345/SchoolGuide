/***@name:C语言校园导游系统
 * 【问题描述】
   @param 设计一个校园导游程序,为来访的客人提供各种信息查询服务。
  【基本要求】
   *
   *TODO:设计中北大学的校园平面图，所含景点不少于10个，以图中顶点表示校内各景点，存放景点名称、代号、简介等信息；以边表示路径，存放路径长度等相关信息。
   *TODO:为来访客人提供图中任意景点相关信息的查询。
   *TODO:为来访客人提供图中任意景点的问路查询，即查询任意两相景点之间的一条最短的简单路径。
   *TODO:求校园图的关节点(待实现）
   *TODO:提供图中任意景点问路查询，即求任意两个景点之间的所有路径。（已实现）
   *TODO:提供校园图中多个景点的最佳访问路线查询，即求途经这多个景点的最佳路径。（已实现，等待测试）
   *
 * @author：陈昊（https://github.com/farewell12345)、冀鹏宇、李照熙
 * @功能：
 *   1. 向csv中手动录入数据，解析csv中的数据（csv解析算法）
 *   2. 计算整张图中各点之间的最短路径（Floyd算法）
 *   3. 输入所处位置和目的地，输出两点之间的最短路径（Floyd算法解析路径向量和距离向量）
 *   4. 输出对应景点的信息（二叉搜索树）
 *   5. 两点之间的所有路径（DFS+栈）
 *   6. 多点的最佳路径（内排序+Floyd）
 * @repositories:本项目所属仓库：
 *   https://github.com/farewell12345/SchoolGuide
 * **/
#include <stdlib.h>
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
int NodeNum = 0; // 结点总个数
int **shortPath = NULL; // 距离向量
int **path = NULL; // 路径向量
Node *head = NULL; // 图
int main(){
    head = readExcel(); // 读取place.csv读取结点信息，作为邻接表头
    frontOrderTrailTree(head); // 对邻接表的结点进行线索化，加快遍历查找速度
    head = readRemote(head); // 将各个顶点进行连接，生成邻接表
    Floyd(head); // 多源最短路径计算，会生成一个shortPath用来存各顶点之间的距离向量，path存各个顶点的路径向量
    while(1) {
        printf("-----------------------------------\n");
        printMap(head); // 打印所有结点的名字和ID
        printf("-----------------------------------\n");
        printf("1.导航\n"
               "2.查询某个景点\n"
               "3.途径多个景点的最佳路径\n"
               "4.两个景点之间的所有路径\n"
               "0. exit\n");
        int i = 0;
        scanf("%d",&i); // 录入选项
        if (i == 0){
            break;
        }
        char *star = malloc(200),*end = malloc(200),*temp_node = malloc(200); // 创建三个可能用到的字符串
        switch(i){
            case 0: // 退出
                break;
            case 1: // 两点间最短路径
                printf("输入你所在的位置的名字或ID:\n");
                scanf("%s",star);
                printf("输入目标位置的名字或ID:\n");
                scanf("%s",end);
                Node *startAddress = searchNodeWithName(head, star); // 根据名字搜索起点
                Node *endAddress = searchNodeWithName(head, end); // 根据名字搜索终点
                startAddress = startAddress == NULL? searchNodeWithID(head,atoi(star)):startAddress; // 根据ID搜索起点
                endAddress = endAddress == NULL? searchNodeWithID(head,atoi(end)):endAddress; // 根据ID搜索终点
                if (endAddress != NULL && startAddress != NULL) {
                    printf("\n%s->%s的最短路径为：\n",startAddress->name,endAddress->name);
                    printShortPath(head, startAddress, endAddress); // 输出两点间最短路径
                } else {
                    printf("输入有误\n");
                }
                break;
            case 2: // 查询某个结点的所有信息
                printf("输入目标位置的名字或ID:\n");
                scanf("%s",temp_node);
                Node *temp = searchNodeWithName(head,temp_node);// 根据名字搜索起点
                if (temp == NULL){
                    if (is_number(temp_node) == false) { // 判断这个字符串是不是纯数字
                        printf("不存在此地点\n");
                        break;
                    }
                    temp = searchNodeWithID(head,atoi(temp_node)); // 根据ID搜索终点
                    if (temp == NULL){
                        printf("不存在此地点\n");
                        break;
                    }
                }
                if (temp!=NULL){
                    printf("%s:(%d):%s\n",temp->name,temp->ID,temp->introduce);
                }else {
                    printf("不存在此地点\n");
                }
                break;
            case 3: // 输出途径的所有景点的最佳路径
                printf("输入起点:\n");
                scanf("%s",star);
                printf("输入终点:\n");
                scanf("%s",end);
                printf("输入途径景点,输入-1结束\n");
                Node** passingNode = malloc(sizeof(Node*)*NodeNum); // 分配输入数组
                startAddress = searchNodeWithName(head,star); // 搜索起点
                if (startAddress==NULL){
                    printf("不存在这个景点！请查询景点表确认");
                    break;
                }
                endAddress = searchNodeWithName(head,end); // 搜索终点（懒得做id适配）
                if (endAddress==NULL){
                    printf("不存在这个景点！请查询景点表确认");
                    break;
                }
                passingNode[0] = startAddress; // 起点存进去
                int passingNum = 1; // 途径的景点数
                scanf("%s",temp_node); // 临时输入景点名
                while (strcmp(temp_node,"-1") != 0){ // 输入-1退出
                    temp = searchNodeWithName(head,temp_node); // 搜索景点
                    if (temp != NULL){
                        /*这里之所以不直接把途径的景点对应的结点存进数组是因为
                         * 在排序的过程中会修改结点本身的相连性，
                         * 最后会导致原有的结点连接关系变得十分混乱*/
                        passingNode[passingNum] = malloc(sizeof(Node));
                        passingNode[passingNum]->ID = temp->ID; // 为了节省内存开支，只需要景点的ID信息和主键信息即可，后会进行内存释放
                        passingNode[passingNum++]->mainId = temp->mainId;
                    }else{
                        printf("没有找到这个结点，请重新输入\n");
                    }
                    scanf("%s", temp_node);
                }
                passingNode[passingNum] = endAddress; // 把终点存进去
                Stack * t = createShortedMap(passingNode,passingNum); // 选择栈来存放对各个景点以距离为权值排序后的结果
                while (StackIsEmpty(t) == false){
                    stackNode* now = popStack(t),*next = getTopStack(t);
                    startAddress = searchNodeWithID(head,now->data->ID); // 根据ID搜索
                    endAddress = searchNodeWithID(head,next->data->ID); // 根据ID搜索
                    printShortPath(head,startAddress,endAddress); // 两两输出最短路径
                    if(next->next == NULL){
                        break;
                    }
                }
                free(t); // 释放所用到的内存
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
                // 输出两点间的所有路径
                break;
        }
        printf("按任意键继续...");
        getchar();
        getchar();
    }
    return 0;
}