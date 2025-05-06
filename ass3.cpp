#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;
int wl=1400;
int wh=900;
void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Default drawing color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wl, wl, -wh, wh);
}
void axis() {
    glColor3f(0.0, 0.0, 0.0); // Black axis
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-wl, 0);
    glVertex2i(wl, 0);
    // Y-axis
    glVertex2i(0, -wh);
    glVertex2i(0, wh);
    glEnd();
}void circle(int r,int h,int k ){

if(r<1){
cout<<"error";
return;
}
int d=3-(2*r);
int x=0;
int y=r;
glBegin(GL_POINTS);
while(x<=y){
if(d<=0){
d=d+4*x+6;
}
else{
d=d+4*(x-y)+10;
y--;
}
x++;
glVertex2i(h+x,k+y);
glVertex2i(h-x,k+y);
glVertex2i(h+x,k-y);
glVertex2i(h-x,k-y);

glVertex2i(h+y,k+x);
glVertex2i(h-y,k+x);
glVertex2i(h+y,k-x);
glVertex2i(h-y,k-x);

}

glEnd();
glFlush();

}
void olympicring() {
    glPointSize(3.0);  // Better size for visibility

    // Top row
    glColor3f(0.0, 0.0, 1.0);  // Blue
    circle(100, -250, 200);

    glColor3f(0.0, 0.0, 0.0);  // Black
    circle(100, 0, 200);

    glColor3f(1.0, 0.0, 0.0);  // Red
    circle(100, 250, 200);

    // Bottom row
    glColor3f(1.0, 1.0, 0.0);  // Yellow
    circle(100, -125, 100);

    glColor3f(0.0, 1.0, 0.0);  // Green
    circle(100, 125, 100);
}


void shape() {
    int x = -600;
    int y = -200;

    // Outer circle
    glColor3f(0.2, 0.2, 0.6);  // Dark Blue
    circle(200, x, y);

    // Triangle
    glColor3f(0.8, 0.0, 0.0);  // Red
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y + 200);
    glVertex2i(x - 173, y - 100);
    glVertex2i(x + 173, y - 100);
    glEnd();

    // Inner circle
    glColor3f(0.0, 0.5, 0.0);  // Green
    circle(80, x, y);
}

void spiral(){
float angle=0.0;
float radius=5.0;
float aninc=0.1;
float rainc=1.5;
glBegin (GL_LINE_STRIP);
while (radius <300){
int x=radius*cos(angle)+700;
int y=radius*sin(angle)-200;
glVertex2i(x,y);
angle+=aninc;
radius+=rainc;


}
glEnd();
glFlush();
}
void concentric(){
circle(200,700,300);
circle(100,700,300);
}

void display(){
glClear(GL_COLOR_BUFFER_BIT);
axis();
glFlush();

}
void menu(int c){
if(c==1){
//simple circle
circle(100,-400,300);

}
else if(c==2) olympicring();
else if(c==3) spiral();
else if(c==4) concentric();
else if(c==5) shape();
glFlush();
}
int main(int argc,char** argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(wl,wh);
glutCreateWindow("circle");
glutDisplayFunc(display);
init();
glutCreateMenu(menu);
glutAddMenuEntry("simple circle",1);
glutAddMenuEntry("olympic",2);
glutAddMenuEntry("spiral",3);
glutAddMenuEntry("cocentric",4);
glutAddMenuEntry("shape",5);
glutAttachMenu(GLUT_RIGHT_BUTTON);


glutMainLoop();
return 0;


}