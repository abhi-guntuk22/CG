#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

struct point
{
    float x,y;
};

point p0,p1,p2,p3;
int cnt=0;
void curve(point p0, point p1, point p2, point p3, int depth = 5) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(p0.x, p0.y);
        glVertex2f(p3.x, p3.y);
        glEnd();
        return;
    }

    point p01 = { (p0.x + p1.x) / 2, (p0.y + p1.y) / 2 };
    point p12 = { (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 };
    point p23 = { (p2.x + p3.x) / 2, (p2.y + p3.y) / 2 };
    point p012 = { (p01.x + p12.x) / 2, (p01.y + p12.y) / 2 };
    point p123 = { (p12.x + p23.x) / 2, (p12.y + p23.y) / 2 };
    point p0123 = { (p012.x + p123.x) / 2, (p012.y + p123.y) / 2 };

    curve(p0, p01, p012, p0123, depth - 1);
    curve(p0123, p123, p23, p3, depth - 1);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //for contro line red
    if(cnt==4){
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(p0.x,p0.y);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glVertex2f(p3.x,p3.y);
    glEnd();
 //draw curve
    glColor3f(0,0,1);
    curve(p0,p1,p2,p3);
    }
   
    
 
    glFlush();
}
void mouse(int btn,int state,int x,int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        if(cnt==0){
            p0={(float)x,(float)(480-y)};
        }
        else if (cnt==1)
        {
            p1={(float)x,(float)(480-y)};
        }
        else if (cnt==2)
        {
            p2={(float)x,(float)(480-y)};
        }
        else if (cnt==3)
        {
            p3={(float)x,(float)(480-y)};
        }

        
            cnt++;
            if(cnt==4){
                glutPostRedisplay();
            }
        }
    
}
void init(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
    glPointSize(3.0);
}
int main(int argc,char** argv){
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(640,480);
 glutCreateWindow("bezier curve");
 glutMouseFunc(mouse);
 glutDisplayFunc(display);
 init();
 glutMainLoop();
 return 0;
 
}