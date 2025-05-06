#include<GL/glut.h>

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
   
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
   
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
     glVertex2i(150,300);
    glVertex2i(350,300);
    glVertex2i(350,450);
    glVertex2i(150,450);
   
    glEnd();
    glFlush();

     glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(170,320);
    glVertex2i(330,320);
    glVertex2i(330,430);
    glVertex2i(170,430);
   
    glEnd();
    glFlush();

     glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2i(230,250);
    glVertex2i(270,250);
    glVertex2i(270,300);
    glVertex2i(230,300);
   
    glEnd();
    glFlush();

     glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2i(200,200);
    glVertex2i(300,200);
    glVertex2i(300,250);
    glVertex2i(200,250);
   
    glEnd();
    glFlush();

}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Assignment 1");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
// #include <GL/glut.h>
// void myinit()
// {
//     glClearColor(1.0,1.0,1.0,0.0);    glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0.0,1280.0,0.0,920);

// }
// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(1.0,0.0,0.0);
//     glBegin(GL_POLYGON);
//     glVertex2i(230,250);
//     glVertex2i(270,250);
//     glVertex2i(270,300);
//     glVertex2i(230,300);
//     glEnd();
//     glFlush();

// }
// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

//     glutInitWindowSize(1240,920);
//     glutCreateWindow("POLYGON");
//     glutDisplayFunc(display);
//     myinit();
//     glutMainLoop();
//     return 0;

// }