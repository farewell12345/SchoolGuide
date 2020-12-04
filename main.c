#include <stdio.h>
#include "DTO/Initmap.h"
#include "ToolFunction/toolsFunction.h"
#include "ReadIndex/readExcel.h"
int NodeNum = 0;
int main(int argc, char *argv[]){
    Node *head = NULL;
    head = readExcel();
    frontOrderTrailTree(head);
    head = readRemote(head);
    Node*t =  searchNodeWithName(head,"文瀛十");
    printf("%s", t->introduce);
    printf("\n");
    printMap(head);
    return 0;
}