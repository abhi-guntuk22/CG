#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;
#define rad  (3.141529/180)
int n;
void curve(float xa,float ya,float xb,float yb,int n){
    float xc,xd,yc,yd,midx,midy;

    xc=(2*xa+xb)/3;
    yc=(2*ya+yb)/3;
    xd=(2*xb+xa)/3;
    yd=(2*yb+ya)/3;

    //calculade mid
    midx= xc+(xd-xc)*cos(60*rad)+(yd-yc)*sin(60*rad);
    midy= yc-(xd-xc)*sin(60*rad)+(yd-yc)*cos(60*rad);

    if(n>0){
        curve(xa,ya,xc,yc,n-1);
        curve(xc,yc,midx,midy,n-1);
        curve(midx,midy,xd,yd,n-1);
        curve(xd,yd,xb,yb,n-1);

    }
    else{
        glVertex2f(xa,ya); glVertex2f(xc,yc);
        glVertex2f(xc,yc); glVertex2f(midx,midy);
        glVertex2f(midx,midy); glVertex2f(xd,yd);
        glVertex2f(xd,yd); glVertex2f(xb,yb);
    }
    
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (n < 10) n++;  // increase iterations up to some limit
        glutPostRedisplay(); // request redraw
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (n > 0) n--;  // decrease iterations
        glutPostRedisplay();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    curve(200,100,400,300,n);
    curve(400,300,0,300,n);
    curve(0,300,200,100,n);
    glEnd();
    glFlush();
}
void init(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

int main(int argc,char** argv){
    cout<<"enter the iteration you want";
    cin>>n;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("koch curve");
    glutMouseFunc(mouse);

    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}   