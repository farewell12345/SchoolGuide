/***C����У԰����ϵͳ
 * ������������
    ���һ��У԰���γ���Ϊ���õĿ����ṩ������Ϣ��ѯ����
  ������Ҫ��
   ����б���ѧ��У԰ƽ��ͼ���������㲻����10������ͼ�ж����ʾУ�ڸ����㣬��ž������ơ����š�������Ϣ���Ա߱�ʾ·�������·�����ȵ������Ϣ��
   Ϊ���ÿ����ṩͼ�����⾰�������Ϣ�Ĳ�ѯ��
   Ϊ���ÿ����ṩͼ�����⾰�����·��ѯ������ѯ�������ྰ��֮���һ����̵ļ�·����
  ��У԰ͼ�Ĺؽڵ�(��ʵ�֣�
  �ṩͼ�����⾰����·��ѯ������������������֮�������·��������ʵ�֣�
  �ṩУ԰ͼ�ж���������ѷ���·�߲�ѯ������;��������������·��������ʵ�֣�
 * author����껣�https://github.com/farewell12345)�������������
 * ���ܣ�
 *   1. ��csv���ֶ�¼�����ݣ�����csv�е����ݣ�csv�����㷨��
 *   2. ��������ͼ�и���֮������·����Floyd�㷨��
 *   3. ��������λ�ú�Ŀ�ĵأ��������֮������·����Floyd�㷨����·�������;���������
 *   4. �����Ӧ�������Ϣ��ǰ������������������
 * ����Ŀ�����ֿ⣺
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
        printf("1.����\n"
               "2.��ѯĳ������\n"
               "3.;�������������·��\n"
               "4.��������֮�������·��\n"
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
                printf("���������ڵ�λ�õ����ֻ�ID:\n");
                scanf("%s",star);
                printf("����Ŀ��λ�õ����ֻ�ID:\n");
                scanf("%s",end);
                Node *startAddress = searchNodeWithName(head, star);
                Node *endAddress = searchNodeWithName(head, end);
                startAddress = startAddress == NULL? searchNodeWithID(head,atoi(star)):startAddress;
                endAddress = endAddress == NULL? searchNodeWithID(head,atoi(end)):endAddress;
                if (endAddress != NULL && startAddress != NULL) {
                    printf("\n%s->%s�����·��Ϊ��\n",startAddress->name,endAddress->name);
                    printShortPath(head, startAddress, endAddress);
                } else {
                    printf("��������\n");
                }
                break;
            case 2:
                printf("����Ŀ��λ�õ����ֻ�ID:\n");
                scanf("%s",temp_node);
                Node *temp = searchNodeWithName(head,temp_node);
                if (temp == NULL){
                    if (is_number(temp_node) == false) {
                        printf("�����ڴ˵ص�\n");
                        break;
                    }
                    temp = searchNodeWithID(head,atoi(temp_node));
                    if (temp == NULL){
                        printf("�����ڴ˵ص�\n");
                        break;
                    }
                }
                if (temp!=NULL){
                    printf("%s:%s\n",temp->name,temp->introduce);
                }
                break;
            case 3:
                printf("�������:\n");
                scanf("%s",star);
                printf("�����յ�:\n");
                scanf("%s",end);
                printf("����;������,����-1����\n");
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
                        printf("û���ҵ������㣬����������\n");
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
                printf("�������:\n");
                scanf("%s",star);
                printf("�����յ�:\n");
                scanf("%s",end);
                printAllPath(searchNodeWithName(head,star),searchNodeWithName(head,end));
                break;
        }
        printf("�����������...");
        getchar();
        getchar();
    }
    return 0;
}