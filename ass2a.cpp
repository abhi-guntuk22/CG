#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

int wl = 1200;
int wh = 700;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    gluOrtho2D(-wl, wl, -wh, wh);
}

void ddaAlgorithm(int x1, int y1, int x2, int y2, int LineType) {
    if (x1 == x2 && y1 == y2) {
        cout << "Error: Source and Destination points are the same!" << endl;
        return;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    int l = max(abs(dx), abs(dy));

    float DX = dx / float(l);
    float DY = dy / float(l);
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= l; i++) {
        if (LineType == 1) { // simple
            glVertex2i(round(x), round(y));
        } else if (LineType == 2) { // dashed
            if (i % 5 == 0)
                glVertex2i(round(x), round(y));
        } else if (LineType == 3) { // dotted
            if (i % 10 == 0)
                glVertex2i(round(x), round(y));
        } else if (LineType == 4) { // dashed-dotted
            int patternLength = 20;
            int dashLength = 5;
            int dotPosition = 12;
            int mod = i % patternLength;
            if (mod < dashLength || mod == dotPosition)
                glVertex2i(round(x), round(y));
        }
        x += DX;
        y += DY;
    }
    glEnd();
    glFlush();
}

void axis() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(-wl, 0);
    glVertex2i(wl, 0);
    glVertex2i(0, -wh);
    glVertex2i(0, wh);
    glEnd();
}

void shape() {
    int s = 4; // scale factor

    ddaAlgorithm(50 * s, 50 * s, 150 * s, 50 * s, 1);
    ddaAlgorithm(150 * s, 50 * s, 140 * s, 30 * s, 1);
    ddaAlgorithm(140 * s, 30 * s, 60 * s, 30 * s, 1);
    ddaAlgorithm(60 * s, 30 * s, 50 * s, 50 * s, 1);
    ddaAlgorithm(100 * s, 50 * s, 130 * s, 50 * s, 1);
    ddaAlgorithm(130 * s, 50 * s, 115 * s, 90 * s, 1);
    ddaAlgorithm(115 * s, 90 * s, 100 * s, 50 * s, 1);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    axis(); // Draw axis after clearing screen
    glFlush();
}

void menu(int index) {
    switch (index) {
        case 1:
            ddaAlgorithm(100, 100, 200, 400, 1); break; // Simple
        case 2:
            ddaAlgorithm(-50, -50, -300, -300, 2); break; // Dashed
        case 3:
            ddaAlgorithm(100, -150, 400, -500, 3); break; // Dotted
        case 4:
            ddaAlgorithm(-50, 50, -400, 400, 4); break; // Dashed-dotted
        case 5:
            shape(); break;
        case 6:
            axis(); break;
    }
    glFlush(); // Ensure drawing updates
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("DDA Assignment 1");

    glutDisplayFunc(display);
    myInit();

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple line", 1);
    glutAddMenuEntry("Dashed line", 2);
    glutAddMenuEntry("Dotted line", 3);
    glutAddMenuEntry("Dashed-Dotted line", 4);
    glutAddMenuEntry("Boat shape", 5);
 
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
