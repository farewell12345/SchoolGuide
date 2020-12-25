/***@name:C����У԰����ϵͳ
 * ������������
   @param ���һ��У԰���γ���,Ϊ���õĿ����ṩ������Ϣ��ѯ����
  ������Ҫ��
   *
   *TODO:����б���ѧ��У԰ƽ��ͼ���������㲻����10������ͼ�ж����ʾУ�ڸ����㣬��ž������ơ����š�������Ϣ���Ա߱�ʾ·�������·�����ȵ������Ϣ��
   *TODO:Ϊ���ÿ����ṩͼ�����⾰�������Ϣ�Ĳ�ѯ��
   *TODO:Ϊ���ÿ����ṩͼ�����⾰�����·��ѯ������ѯ�������ྰ��֮���һ����̵ļ�·����
   *TODO:��У԰ͼ�Ĺؽڵ�(��ʵ�֣�
   *TODO:�ṩͼ�����⾰����·��ѯ������������������֮�������·��������ʵ�֣�
   *TODO:�ṩУ԰ͼ�ж���������ѷ���·�߲�ѯ������;��������������·��������ʵ�֣��ȴ����ԣ�
   *TODO:GUI(ʹ��EGE��ܣ�
 * @author����껣�https://github.com/farewell12345)�������������
 * @���ܣ�
 *   1. ��csv���ֶ�¼�����ݣ�����csv�е����ݣ�csv�����㷨��
 *   2. ��������ͼ�и���֮������·����Floyd�㷨��
 *   3. ��������λ�ú�Ŀ�ĵأ��������֮������·����Floyd�㷨����·�������;���������
 *   4. �����Ӧ�������Ϣ��������������
 *   5. ����֮�������·����DFS+ջ��
 *   6. �������·����������+Floyd��
 * @repositories:����Ŀ�����ֿ⣺
 *   https://github.com/farewell12345/SchoolGuide
 * **/
#include <cstdlib>
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
#include "GUI/GUI.h"
int NodeNum; // ����ܸ���
int **shortPath = NULL; // ��������
int **path = NULL; // ·������
Node *head = NULL; // ͼ
int main(int argc, char** argv){
    NodeNum = 0;
    head = readExcel(); // ��ȡplace.csv��ȡ�����Ϣ����Ϊ�ڽӱ�ͷ
    frontOrderTrailTree(head); // ���ڽӱ�Ľ��������������ӿ���������ٶ�
    head = readRemote(head); // ����������������ӣ������ڽӱ�
    Floyd(head); // ��Դ���·�����㣬������һ��shortPath�����������֮��ľ���������path����������·������
    initWindows(head);
    while(true) {
        printf("-----------------------------------\n");
        printMap(head); // ��ӡ���н������ֺ�ID
        printf("-----------------------------------\n");
        printf("1.����\n"
               "2.��ѯĳ������\n"
               "3.;�������������·��\n"
               "4.��������֮�������·��\n"
               "0. exit\n");
        int i = 0;
        scanf("%d",&i); // ¼��ѡ��
        if (i == 0){
            break;
        }
        char *star =(char*) malloc(200),*end = (char*)malloc(200),*temp_node =(char*) malloc(200); // �������������õ����ַ���
        Node *temp = NULL;
        Node *startAddress = NULL,*endAddress = NULL;
        Node** passingNode = NULL;
        Stack * t = NULL;
        int passingNum = 1; // ;���ľ�����
        switch(i){
//            case 0: // �˳�
//                break;
//            case 1: // ��������·��
//                printf("���������ڵ�λ�õ����ֻ�ID:\n");
//                scanf("%s",star);
//                printf("����Ŀ��λ�õ����ֻ�ID:\n");
//                scanf("%s",end);
//                startAddress = searchNodeWithName(head, star); // ���������������
//                endAddress = searchNodeWithName(head, end); // �������������յ�
//                if (startAddress == NULL) {
//                    startAddress = searchNodeWithID(head, atoi(star));
//                } else {
//                    startAddress = startAddress;
//                } // ����ID�������
//                if (endAddress == NULL) {
//                    endAddress = searchNodeWithID(head, atoi(end));
//                } else {
//                    endAddress = endAddress;
//                } // ����ID�����յ�
//                if (endAddress != NULL && startAddress != NULL) {
//                    printf("\n%s->%s�����·��Ϊ��\n",startAddress->name,endAddress->name);
//                    printShortPath(head, startAddress, endAddress); // �����������·��
//                } else {
//                    printf("��������\n");
//                }
//                break;
//            case 2: // ��ѯĳ������������Ϣ
//                printf("����Ŀ��λ�õ����ֻ�ID:\n");
//                scanf("%s",temp_node);
//                temp = searchNodeWithName(head,temp_node);// ���������������
//                if (temp == NULL){
//                    if (is_number(temp_node) == false) { // �ж�����ַ����ǲ��Ǵ�����
//                        printf("�����ڴ˵ص�\n");
//                        break;
//                    }
//                    temp = searchNodeWithID(head,atoi(temp_node)); // ����ID�����յ�
//                    if (temp == NULL){
//                        printf("�����ڴ˵ص�\n");
//                        break;
//                    }
//                }
//                printf("%s:(%d):%s\n", temp->name, temp->ID, temp->introduce);
//                break;
//            case 3: // ���;�������о�������·��
//                printf("�������:\n");
//                scanf("%s",star);
//                printf("�����յ�:\n");
//                scanf("%s",end);
//                printf("����;������,����-1����\n");
//                passingNode =(Node**) malloc(sizeof(Node*)*NodeNum); // ������������
//                startAddress = searchNodeWithName(head,star); // �������
//                if (startAddress==NULL){
//                    printf("������������㣡���ѯ�����ȷ��");
//                    break;
//                }
//                endAddress = searchNodeWithName(head,end); // �����յ㣨������id���䣩
//                if (endAddress==NULL){
//                    printf("������������㣡���ѯ�����ȷ��");
//                    break;
//                }
//                passingNode[0] = startAddress; // �����ȥ
//
//                scanf("%s",temp_node); // ��ʱ���뾰����
//                while (strcmp(temp_node,"-1") != 0){ // ����-1�˳�
//                    temp = searchNodeWithName(head,temp_node); // ��������
//                    if (temp != NULL){
//                        /*����֮���Բ�ֱ�Ӱ�;���ľ����Ӧ�Ľ������������Ϊ
//                         * ������Ĺ����л��޸Ľ�㱾��������ԣ�
//                         * ���ᵼ��ԭ�еĽ�����ӹ�ϵ���ʮ�ֻ���*/
//                        passingNode[passingNum] =(Node*) malloc(sizeof(Node));
//                        passingNode[passingNum]->ID = temp->ID; // Ϊ�˽�ʡ�ڴ濪֧��ֻ��Ҫ�����ID��Ϣ��������Ϣ���ɣ��������ڴ��ͷ�
//                        passingNode[passingNum++]->mainId = temp->mainId;
//                    }else{
//                        printf("û���ҵ������㣬����������\n");
//                    }
//                    scanf("%s", temp_node);
//                }
//                passingNode[passingNum] = endAddress; // ���յ���ȥ
//                t= createShortedMap(passingNode,passingNum); // ѡ��ջ����ŶԸ��������Ծ���ΪȨֵ�����Ľ��
//                while (StackIsEmpty(t) == false){
//                    stackNode* now = popStack(t),*next = getTopStack(t);
//                    startAddress = searchNodeWithID(head,now->data->ID); // ����ID����
//                    endAddress = searchNodeWithID(head,next->data->ID); // ����ID����
//                    printShortPath(head,startAddress,endAddress); // ����������·��
//                    if(next->next == NULL){
//                        break;
//                    }
//                    free(now);
//                }
//                free(t); // �ͷ����õ����ڴ�
//                for (int j = 1; j < passingNum - 1; ++j) {
//                    free(passingNode[j]);
//                }
//                break;
            case 4:
                printf("�������:\n");
                scanf("%s",star);
                printf("�����յ�:\n");
                scanf("%s",end);
                printAllPath(searchNodeWithName(head,star),searchNodeWithName(head,end));
                // �������������·��
                break;
        }
        printf("�����������...");
        getchar();
        getchar();
    }
    return 0;
}