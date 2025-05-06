#include <GL/glut.h>
#include <iostream>
using namespace std;

#define MAX 20

int xmin = -100, ymin = -100, xmax = 100, ymax = 100;

// Rotated square (diamond) - all points outside the box
int poly[MAX][2] = {
    {0, 150},     // top
    {150, 0},     // right
    {0, -150},    // bottom
    {-150, 0}     // left
};
int n = 4;

int clipped[MAX][2];
int clipped_n = 0;
bool isClipped = false;

void drawPolygon(int p[][2], int n, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2i(p[i][0], p[i][1]);
    glEnd();
    glFlush();
}

void drawClippingWindow() {
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
    glFlush();
}

bool inside(int x, int y, int edge) {
    if (edge == 0) return x >= xmin;
    if (edge == 1) return x <= xmax;
    if (edge == 2) return y >= ymin;
    if (edge == 3) return y <= ymax;
    return false;
}

void intersect(int x1, int y1, int x2, int y2, int edge, int& x, int& y) {
    float dx = x2 - x1, dy = y2 - y1;
    float m = (dx != 0) ? dy / dx : 1e9;

    if (edge == 0) {
        x = xmin;
        y = y1 + (xmin - x1) * m;
    } else if (edge == 1) {
        x = xmax;
        y = y1 + (xmax - x1) * m;
    } else if (edge == 2) {
        y = ymin;
        x = x1 + (1.0 / m) * (ymin - y1);
    } else if (edge == 3) {
        y = ymax;
        x = x1 + (1.0 / m) * (ymax - y1);
    }
}

void suthHodgClip() {
    int input[MAX][2], output[MAX][2];
    int in_n = n, out_n;

    for (int i = 0; i < n; i++) {
        input[i][0] = poly[i][0];
        input[i][1] = poly[i][1];
    }

    for (int edge = 0; edge < 4; edge++) {
        out_n = 0;
        for (int i = 0; i < in_n; i++) {
            int x1 = input[i][0], y1 = input[i][1];
            int x2 = input[(i + 1) % in_n][0], y2 = input[(i + 1) % in_n][1];

            bool in1 = inside(x1, y1, edge);
            bool in2 = inside(x2, y2, edge);

            if (in1 && in2) {
                output[out_n][0] = x2;
                output[out_n][1] = y2;
                out_n++;
            } else if (in1 && !in2) {
                int x, y;
                intersect(x1, y1, x2, y2, edge, x, y);
                output[out_n][0] = x;
                output[out_n][1] = y;
                out_n++;
            } else if (!in1 && in2) {
                int x, y;
                intersect(x1, y1, x2, y2, edge, x, y);
                output[out_n][0] = x;
                output[out_n][1] = y;
                out_n++;
                output[out_n][0] = x2;
                output[out_n][1] = y2;
                out_n++;
            }
        }

        in_n = out_n;
        for (int i = 0; i < out_n; i++) {
            input[i][0] = output[i][0];
            input[i][1] = output[i][1];
        }
    }

    clipped_n = in_n;
    for (int i = 0; i < clipped_n; i++) {
        clipped[i][0] = input[i][0];
        clipped[i][1] = input[i][1];
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    if (isClipped) {
        drawPolygon(clipped, clipped_n, 0, 1, 0); // green
    } else {
        drawPolygon(poly, n, 1, 0, 0); // red
    }
    glFlush();
}

void menu(int id) {
    if (id == 1) {
        suthHodgClip();
        isClipped = true;
    } else if (id == 2) {
        isClipped = false;
    } else if (id == 3) {
        exit(0);
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Clipping - Rotated Square (Diamond)");

    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Clip Polygon", 1);
    glutAddMenuEntry("Reset Polygon", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
