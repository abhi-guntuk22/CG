#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

void init(void){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}
int mx,my,choice;
float boundarycolor[3]={0,0,0};
float interiorcolor[3]={1,1,1};
float floodcolor[3]={1,0,0};
float boundcolor[3]={0,0,1};
float readpixel[3];
void getpixel(int x,int y,float *color){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}
void setpixel(int x,int y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();

}
void floodfill(int x,int y){
    getpixel(x,y,readpixel);
    if(readpixel[0]==interiorcolor[0] && readpixel[1]==interiorcolor[1] && readpixel[2]==interiorcolor[2]){
        glColor3fv(floodcolor);
        setpixel(x,y);
        floodfill(x + 1, y);
        floodfill(x, y + 1);
        floodfill(x - 1, y);
        floodfill(x, y - 1);
        glEnd();
        glFlush();
    }
}
void boundaryfill(int x, int y){
    if(x>640 || x<0 || y>480 || y<0){
        return;
    }
    getpixel(x,y,readpixel);
    if((readpixel[0]!=boundarycolor[0] ||readpixel[1]!=boundarycolor[1] ||readpixel[2]!=boundarycolor[2] )
        &&(readpixel[0] != boundcolor[0] || readpixel[1] != boundcolor[1] || readpixel[2] != boundcolor[2])
      ){
      glColor3fv(boundcolor);
      setpixel(x,y);
      boundaryfill(x + 1, y);
      boundaryfill(x, y + 1);
      boundaryfill(x, y - 1);
      boundaryfill(x - 1, y);
     
      glFlush();
      }
}
void mymouse(int btn,int state,int x,int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        mx=x;
        my=480-y;
        switch(choice){
            case 1: floodfill(mx,my); break;
            case 2: boundaryfill(mx,my); break;
        }
    }
}
void shape(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200,150);
    glVertex2i(300,150);
    glVertex2i(300,350);
    glVertex2i(200,350);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2i(300,150);
    glVertex2i(400,150);
    glVertex2i(400,350);
    glVertex2i(300,350);
    glEnd();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    shape();
    glFlush();
}
void menu(int opt){
    switch (opt)
    {
    case 1: choice=opt; break;
    case 2: choice=opt; break;
    case 3: exit(0); break;
    }
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("filling");
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("flood fill",1);
    glutAddMenuEntry("boundary fill",2);
    glutAddMenuEntry("exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    glutMainLoop();
    return 0;

}