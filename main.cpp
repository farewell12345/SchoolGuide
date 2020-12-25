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
   *TODO:GUI(使用EGE框架）
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
#include <cstdlib>
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
#include "GUI/GUI.h"
int NodeNum; // 结点总个数
int **shortPath = NULL; // 距离向量
int **path = NULL; // 路径向量
Node *head = NULL; // 图
int main(){
    NodeNum = 0;
    head = readExcel(); // 读取place.csv读取结点信息，作为邻接表头
    frontOrderTrailTree(head); // 对邻接表的结点进行线索化，加快遍历查找速度
    head = readRemote(head); // 将各个顶点进行连接，生成邻接表
    Floyd(head); // 多源最短路径计算，会生成一个shortPath用来存各顶点之间的距离向量，path存各个顶点的路径向量
    initWindows(head);
    return 0;
}