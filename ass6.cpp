#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

// Initial square points placed in the first quadrant
float square[4][3] = {
    {50, 50, 1},
    {150, 50, 1},
    {150, 150, 1},
    {50, 150, 1}
};

float tx = 150;          // Translation on X-axis
float ty = 150;          // Translation on Y-axis
float angle = 45.0;      // Rotation angle
float refx = 100, refy = 100; // Reference point for rotation (center of the square)
float sclx = 1.5, scaly = 1.5; // Scaling factors
float shx = 1.0;         // Shearing factor

// Matrix multiplication function
void matrixmultiply(float mat[3][3], float point[3]) {
    float res[3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i] += mat[i][j] * point[j];
        }
    }
    for (int i = 0; i < 3; i++) {
        point[i] = res[i];
    }
}

// Function to draw the axis
void axis() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(500, 0); // Positive X-axis
    glVertex2i(0, 0);
    glVertex2i(0, 500); // Positive Y-axis
    glEnd();
}

// Function to draw the square (wireframe)
void drawSquare(float sqr[4][3]) {
    glColor3f(1.0, 0.0, 0.0); // Red color for the square outline
    glBegin(GL_LINE_LOOP);  // Draw outline of the square
    for (int i = 0; i < 4; i++) {
        glVertex2i(sqr[i][0], sqr[i][1]);
    }
    glEnd();
}

// Function to reset the square position (centered at the origin)
void resetSquare() {
    square[0][0] = 50; square[0][1] = 50; square[0][2] = 1;
    square[1][0] = 150; square[1][1] = 50; square[1][2] = 1;
    square[2][0] = 150; square[2][1] = 150; square[2][2] = 1;
    square[3][0] = 50; square[3][1] = 150; square[3][2] = 1;

    // Update reference point (center of square)
    refx = 100;
    refy = 100;
}

// Function to perform scaling
void scaling() {
    float scalematrix[3][3] = {
        {sclx, 0, 0},
        {0, scaly, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++) {
        matrixmultiply(scalematrix, square[i]);
    }
}

// Function to perform rotation
void rotation() {
    float rad = angle * 3.1415 / 180; // Convert to radians
    float translateorigin[3][3] = {
        {1, 0, -refx},
        {0, 1, -refy},
        {0, 0, 1}
    };
    float rotate[3][3] = {
        {cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad), 0},
        {0, 0, 1}
    };
    float translateback[3][3] = {
        {1, 0, refx},
        {0, 1, refy},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++) {
        matrixmultiply(translateorigin, square[i]);
        matrixmultiply(rotate, square[i]);
        matrixmultiply(translateback, square[i]);
    }
}

// Function to perform translation
void translation() {
    float transmatrix[3][3] = {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++) {
        matrixmultiply(transmatrix, square[i]);
    }
}

// Function to perform shearing
void shearing() {
    float sheramatrix[3][3] = {
        {1, -shx, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++) {
        matrixmultiply(sheramatrix, square[i]);
    }
}

// Function to reflect across X-axis
void reflect() {
    float reflectmatrix[3][3] = {
        {1, 0, 0},
        {0, -1, 0},
        {0, 0, 1}
    };
    for (int i = 0; i < 4; i++) {
        matrixmultiply(reflectmatrix, square[i]);
    }
}

// Function to display the square and axes
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    axis();           // Draw the axes
    drawSquare(square); // Draw the square (wireframe)
    glFlush();
}

// Menu options for transformations
void menu(int opt) {
    resetSquare();
    switch (opt) {
    case 1: scaling(); break;
    case 2: translation(); break;
    case 3: rotation(); break;
    case 4: shearing(); break;
    case 5: resetSquare(); break;
    case 6: exit(0); break;
    case 7: // Clockwise Rotation
        angle = -45.0;
        rotation();
        break;
    case 8: // Anticlockwise Rotation
        angle = 45.0;
        rotation();
        break;
    }
    glutPostRedisplay();
}

// Initialize OpenGL
void myinit() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);  // Only considering the first quadrant
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("2D Transformations - Square (First Quadrant)");
    myinit();

    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("1. Scaling about origin", 1);
    glutAddMenuEntry("2. Translation", 2);
    glutAddMenuEntry("3. Rotation (anticlockwise 45°)", 3);
    glutAddMenuEntry("4. Shearing", 4);
    glutAddMenuEntry("5. Reset Square", 5);
    glutAddMenuEntry("7. Clockwise Rotation (45°)", 7);
    glutAddMenuEntry("8. Anticlockwise Rotation (45°)", 8);
    glutAddMenuEntry("9. Exit", 6);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
