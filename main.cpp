#include <cstdio>
#include "Initmap.h"
#include "toolsFunction.h"
#include "readExcel.h"
#include <GL/glut.h>
int nodeNum = 0;
void ChangeSize(GLsizei w,GLsizei h){
    if(w<1) w=1;
    if(h<1) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-30.0,30.0,-30.0*(GLfloat)h/(GLfloat)w,30.0*(GLfloat)h/(GLfloat)w,-50.0,50.0);
    else
        glOrtho(-30.0*(GLfloat)w/(GLfloat)h,30.0*(GLfloat)w/(GLfloat)h,-30.0,30.0,-50.0,50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0,0.0f,1.0f,0.0f);
}
void DrawMyObjects() {
    //画四边形
    glBegin(GL_QUADS);
    glVertex2f(-30,-30);
    glVertex2f(-55,-10);
    glVertex2f(-10,-5);
    glVertex2f(-10,-20);
    glColor3f(0.5,0.7,0.2);
    glEnd();
}
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    DrawMyObjects();
    glFlush();
}
int main(int argc, char *argv[]){
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//    glutInitWindowSize(600,600);
//    glutCreateWindow("My first");
//    glClearColor(0.7,0.4,0.9,0.5);
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(RenderScene);
//    glutMainLoop();
    node *head = createMap();
    node *fuck[6];
    int test[6] = {5,2,1,3,4,6};
    char *p = "北京",*introduce = "我草泥马";
    setName(head,p);
    head->mainId = 0;
    setIntroduce(head,introduce);
    setID(head,1);
    readExcel(head);
    for (int i = 0; i < 6; ++i) {
        fuck[i] = initNode();
        setID(fuck[i],test[i]);
        InsertNode(head,fuck[i]);
        setIntroduce(fuck[i],p);
        fuck[i]->mainId = i+1;
        pushSequenceNode(head,fuck[i]);
    }
    setName(fuck[0],"太原");
    setName(fuck[1],"石家庄");
    setName(fuck[2],"中北大学");
    setName(fuck[3],"北京大学");
    setName(fuck[4],"太原理工大学");
    setName(fuck[5],"司马大学");
//    remoteNode(head,fuck[0],4);
//    remoteNode(fuck[0],fuck[1],2);
//    remoteNode(fuck[0],fuck[4],1);
//    remoteNode(fuck[0],fuck[2],6);
//    remoteNode(fuck[1],fuck[3],7);
//    remoteNode(fuck[3],fuck[4],9);
//    remoteNode(fuck[2],fuck[5],10);
//    remoteNode(fuck[4],fuck[5],11);
//    printf("\n");
    frontOrderTrailTree(head);
    printf("%s", preOrderTrailTree(head,"工训中心")->introduce);
//    printMap(head);
    printf("\n");

    return 0;
}