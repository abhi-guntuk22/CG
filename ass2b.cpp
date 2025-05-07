#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

int wl = 1400;
int wh = 900;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3i(0, 0, 0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-wl, wl, -wh, wh);
}

int sign(int val) {
    if (val < 0) return -1;
    else if (val == 0) return 0;
    else return 1;
}

void BAlgorithm(int x1, int y1, int x2, int y2, int LineType) {
    if (x1 == x2 && y1 == y2) {
        cout << "Error: Source and Destination points are the same! Line cannot be drawn." << endl;
        return;
    }

    int x = x1;
    int y = y1;
    int Dx = abs(x2 - x1);
    int Dy = abs(y2 - y1);
    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int interchange = 0;

    if (Dy > Dx) {
        swap(Dx, Dy);
        interchange = 1;
    }

    int e = 2 * Dy - Dx;

    glBegin(GL_POINTS);
    for (int i = 1; i <= Dx; i++) {
        // Line styling
        if (LineType == 1) {
            glVertex2i(x, y); // Solid
        } else if (LineType == 2) {
            if (i % 10 < 5) glVertex2i(x, y); // Dashed
        } else if (LineType == 3) {
            if (i % 10 == 0) glVertex2i(x, y); // Dotted
        } else if (LineType == 4) {
            if (i % 15 < 5 || i % 15 == 7) {
                glVertex2i(x, y); // Dashed-Dotted
            }
            
        }

        while (e >= 0) {
            if (interchange == 1) x += s1;
            else y += s2;
            e -= 2 * Dx;
        }

        if (interchange == 1) y += s2;
        else x += s1;

        e += 2 * Dy;
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

void drawDiag() {
    // Outer square
    BAlgorithm(300, -300, 750, -300, 1);
    BAlgorithm(300, -700, 750, -700, 1);
    BAlgorithm(300, -300, 300, -700, 1);
    BAlgorithm(750, -300, 750, -700, 1);

    // Inner diamond
    BAlgorithm(300, -500, 525, -300, 1);
    BAlgorithm(525, -300, 750, -500, 1);
    BAlgorithm(750, -500, 525, -700, 1);
    BAlgorithm(525, -700, 300, -500, 1);

    // Inner square
    BAlgorithm(412, -400, 637, -400, 1);
    BAlgorithm(637, -400, 637, -600, 1);
    BAlgorithm(637, -600, 412, -600, 1);
    BAlgorithm(412, -600, 412, -400, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    axis();
    glFlush();
}

void menu(int index) {
    switch (index) {
        case 1:
            BAlgorithm(100, 100, 200, 200, 1); // Solid line
            break;
        case 2:
            BAlgorithm(-100, -50, -100, -300, 2); // Dashed line
            break;
        case 3:
            BAlgorithm(-300, -450, -100, 500, 3); // Dotted line
            break;
        case 4:
            BAlgorithm(-50, 50, -400, 400, 4); // Dashed-Dotted line
            break;
        case 5:
            drawDiag(); // Draw custom shape
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wl, wh);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Bresenham's Line Algorithm with Styles");

    myInit();
    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 1);
    glutAddMenuEntry("Dashed Line", 2);
    glutAddMenuEntry("Dotted Line", 3);
    glutAddMenuEntry("Dashed-Dotted Line", 4);
    glutAddMenuEntry("Draw Shape", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
