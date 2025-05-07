#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

// Original square in first quadrant
float square[4][3] = {
    {50, 50, 1},
    {150, 50, 1},
    {150, 150, 1},
    {50, 150, 1}
};

float tx = 150, ty = 150;              // Translation values
float angle = 45.0;                    // Rotation angle
float refx = 100, refy = 100;          // Rotation reference
float sclx = 1.5, scaly = 1.5;         // Scaling factors
float shx = 1.0;                       // Shear factor (used in all types)

// Matrix multiplication
void matrixmultiply(float mat[3][3], float point[3]) {
    float res[3] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res[i] += mat[i][j] * point[j];
    for (int i = 0; i < 3; i++)
        point[i] = res[i];
}

// Draw axes
void axis() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(500, 0); // X-axis
    glVertex2i(0, 0);
    glVertex2i(0, 500); // Y-axis
    glEnd();
}

// Draw square
void drawSquare(float sqr[4][3]) {
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2i(sqr[i][0], sqr[i][1]);
    glEnd();
}

// Reset square to original
void resetSquare() {
    square[0][0] = 50;  square[0][1] = 50;  square[0][2] = 1;
    square[1][0] = 150; square[1][1] = 50;  square[1][2] = 1;
    square[2][0] = 150; square[2][1] = 150; square[2][2] = 1;
    square[3][0] = 50;  square[3][1] = 150; square[3][2] = 1;

    refx = 100;
    refy = 100;
}

// Scaling
void scaling() {
    float mat[3][3] = {
        {sclx, 0, 0},
        {0, scaly, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Translation
void translation() {
    float mat[3][3] = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Rotation about a point
void rotation() {
    float rad = angle * 3.1415 / 180;
    float toOrigin[3][3] = {
        {1, 0, -refx},
        {0, 1, -refy},
        {0, 0, 1}
    };
    float rot[3][3] = {
        {cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad), 0},
        {0, 0, 1}
    };
    float back[3][3] = {
        {1, 0, refx},
        {0, 1, refy},
        {0, 0, 1}
    };

    for (int i = 0; i < 4; i++) {
        matrixmultiply(toOrigin, square[i]);
        matrixmultiply(rot, square[i]);
        matrixmultiply(back, square[i]);
    }
}

// Shearing in X-direction
void shearingX() {
    float mat[3][3] = {
        {1, shx, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Shearing in Y-direction
void shearingY() {
    float mat[3][3] = {
        {1, 0, 0},
        {shx, 1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Shearing in both directions
void shearingXY() {
    float mat[3][3] = {
        {1, shx, 0},
        {shx, 1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Reflection across X-axis
void reflectX() {
    float mat[3][3] = {
        {1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++)
        matrixmultiply(mat, square[i]);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    axis();
    drawSquare(square);
    glFlush();
}

// Menu for transformations
void menu(int opt) {
    resetSquare();  // Always start from original
    switch (opt) {
        case 1: scaling(); break;
        case 2: translation(); break;
        case 3: rotation(); break;
        case 4: shearingX(); break;
        case 5: shearingY(); break;
        case 6: shearingXY(); break;
        case 7: reflectX(); break;
        case 8: angle = -45.0; rotation(); break;
        case 9: angle = 45.0; rotation(); break;
        case 10: resetSquare(); break;
        case 11: exit(0); break;
    }
    glutPostRedisplay();
}

// OpenGL initialization
void myinit() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);  // First quadrant view
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("2D Transformations - Square (Matrix Form)");
    myinit();

    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("1. Scaling about origin", 1);
    glutAddMenuEntry("2. Translation", 2);
    glutAddMenuEntry("3. Rotation (Anticlockwise 45°)", 3);
    glutAddMenuEntry("4. Shearing in X-direction", 4);
    glutAddMenuEntry("5. Shearing in Y-direction", 5);
    glutAddMenuEntry("6. Shearing in XY-direction", 6);
    glutAddMenuEntry("7. Reflection across X-axis", 7);
    glutAddMenuEntry("8. Rotation Clockwise (45°)", 8);
    glutAddMenuEntry("9. Rotation Anticlockwise (45°)", 9);
    glutAddMenuEntry("10. Reset", 10);
    glutAddMenuEntry("11. Exit", 11);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
