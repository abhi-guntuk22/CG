#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<iostream>
using namespace std;

int A[20][3], C[20][3], n;
float B[3][3];
int shx, shy, tx, ty, sx, sy;

void lineDDA(int x1, int y1, int x2, int y2);
void translation();
void scaling();
void shearing();
void rotation();
void reflection();
void multiply();
void unit();
void display();
void menu(int);

void lineDDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void unit()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            B[i][j] = (i == j) ? 1 : 0;
}

void translation()
{
    cout << "Enter tx and ty: ";
    cin >> tx >> ty;
    unit();
    B[2][0] = tx;
    B[2][1] = ty;
    multiply();
}

void scaling()
{
    cout << "Enter sx and sy: ";
    cin >> sx >> sy;
    unit();
    B[0][0] = sx;
    B[1][1] = sy;
    multiply();
}

void shearing()
{
    int ch;
    cout<<"\nEnter the choice\n";
    cout<<"\n1. X axis Shearing\n";
    cout<<"\n2. Y axis Shearing\n";
    cout<<"\n3. X and Y both Shearing\n";
    cin>>ch;
    unit(); // Initialize matrix as Identity matrix

    if(ch == 1)
    {
        cout<<"\nEnter the value of shx: ";
        cin>>shx;
        B[0][1] = shx;  // Correct: X-axis shearing (x' = x + shx*y)
        multiply();
    }
    else if(ch == 2)
    {
        cout<<"\nEnter the value of shy: ";
        cin>>shy;
        B[1][0] = shy;  // Correct: Y-axis shearing (y' = y + shy*x)
        multiply();
    }
    else if(ch == 3)
    {
        cout<<"\nEnter the value of shx: ";
        cin>>shx;
        B[0][1] = shx;
        cout<<"\nEnter the value of shy: ";
        cin>>shy;
        B[1][0] = shy;
        multiply();
    }
    else
    {
        cout<<"\nWrong choice\n";
    }
}


void rotation()
{
    float angle, ch;
    cout << "Enter rotation angle: ";
    cin >> angle;
    float rad = (angle * 3.14) / 180;

    unit();
    cout << "1. Clockwise\n2. Anti-clockwise\nEnter your choice: ";
    cin >> ch;

    if (ch == 1)
    {
        B[0][0] = cos(rad);
        B[0][1] = sin(rad);
        B[1][0] = -sin(rad);
        B[1][1] = cos(rad);
    }
    else if (ch == 2)
    {
        B[0][0] = cos(rad);
        B[0][1] = -sin(rad);
        B[1][0] = sin(rad);
        B[1][1] = cos(rad);
    }
    else
    {
        cout << "Wrong choice!";
        return;
    }

    multiply();
}

void reflection()
{
    int ch;
    cout << "\n1. Reflect about X-axis\n2. Reflect about Y-axis\nEnter your choice: ";
    cin >> ch;

    unit();
    if (ch == 1)
        B[1][1] = -1;
    else if (ch == 2)
        B[0][0] = -1;
    else
    {
        cout << "Wrong choice!";
        return;
    }

    multiply();
}

void multiply()
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<3;j++)
        {
            C[i][j]=0;
            for(k=0;k<3;k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
        C[i][2]=1;
    }

    // IMPORTANT: Copy C into A after transformation
    for(i=0;i<n;i++)
    {
        A[i][0] = C[i][0];
        A[i][1] = C[i][1];
        A[i][2] = C[i][2];
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    lineDDA(320, 0, 320, 480);
    lineDDA(0, 240, 640, 240);

    glColor3f(0.0, 0.0, 1.0);
    for (int i = 0; i < n - 1; i++)
        lineDDA(A[i][0] + 320, A[i][1] + 240, A[i + 1][0] + 320, A[i + 1][1] + 240);
    lineDDA(A[n - 1][0] + 320, A[n - 1][1] + 240, A[0][0] + 320, A[0][1] + 240);

    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < n - 1; i++)
        lineDDA(C[i][0] + 320, C[i][1] + 240, C[i + 1][0] + 320, C[i + 1][1] + 240);
    lineDDA(C[n - 1][0] + 320, C[n - 1][1] + 240, C[0][0] + 320, C[0][1] + 240);

    glFlush();
}

void menu(int choice)
{
    switch (choice)
    {
    case 1:
        translation();
        break;
    case 2:
        scaling();
        break;
    case 3:
        shearing();
        break;
    case 4:
        rotation();
        break;
    case 5:
        reflection();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void Init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main(int argc, char **argv)
{
    cout << "Enter number of vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter x and y coordinates for vertex " << i + 1 << ": ";
        cin >> A[i][0] >> A[i][1];
        A[i][2] = 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations with Shearing");

    Init();
    glutDisplayFunc(display);

    glutCreateMenu(menu);
    glutAddMenuEntry("Translation", 1);
    glutAddMenuEntry("Scaling", 2);
    glutAddMenuEntry("Shearing", 3);
    glutAddMenuEntry("Rotation", 4);
    glutAddMenuEntry("Reflection", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;#include <GL/glut.h>
    #include <math.h>
    
    float angle = 0.0f;
    float birdX = -400.0f;
    float flagY = 50.0f;  // Start height of the flag (initially rolled up)
    float flagHeight = 0.0f;  // To control how much of the flag is visible
    float rodHeight = 0.0f;   // Height of the pole (initially zero for animation)
    float birdSpeed = 1.0f;
    float cloudX[3] = {-200.0f, -400.0f, -600.0f};  // Initial position of clouds
    float cloudSpeed[3] = {0.1f, 0.08f, 0.12f};     // Different speeds for clouds
    
    void drawCircle(float cx, float cy, float r, int num_segments) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < num_segments; i++) {
            float theta = 2.0f * 3.1416f * float(i) / float(num_segments);
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            glVertex2f(x + cx, y + cy);
        }
        glEnd();
    }
    
    void drawFlag() {
        glPushMatrix();
        glTranslatef(0, flagY, 0);
    
        // Flag starts unrolling and rising
        float wave = sin(angle) * 5;
    
        // Saffron stripe
        glColor3f(1.0f, 0.6f, 0.2f);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 60; i++) {
            float x = i * 2;
            float y = 120 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        for (int i = 60; i >= 0; i--) {
            float x = i * 2;
            float y = 100 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        glEnd();
    
        // White stripe
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 60; i++) {
            float x = i * 2;
            float y = 100 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        for (int i = 60; i >= 0; i--) {
            float x = i * 2;
            float y = 80 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        glEnd();
    
        // Green stripe
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 60; i++) {
            float x = i * 2;
            float y = 80 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        for (int i = 60; i >= 0; i--) {
            float x = i * 2;
            float y = 60 + sin(i * 0.2 + angle) * 5;
            glVertex2f(x, y);
        }
        glEnd();
    
        // Ashoka Chakra
        glColor3f(0.0f, 0.0f, 1.0f);
        drawCircle(60, 90, 5, 30);
        glPopMatrix();
    }
    
    void drawPole() {
        glColor3f(0.4f, 0.2f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0, 50);
        glVertex2f(5, 50);
        glVertex2f(5, 250);
        glVertex2f(0, 250);
        glEnd();
    }
    
    void drawBirds() {
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < 5; i++) {
            float x = birdX + i * 60;
            float y = 300 + sin(angle + i) * 20;  // Increase the bird's dynamic movement
    
            // Natural bird shape (with two wings)
            glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + 10, y + 10);
            glVertex2f(x + 10, y + 10);
            glVertex2f(x + 20, y);
            glEnd();
        }
    }
    
    void drawCloud(float x, float y) {
        glColor3f(1.0f, 1.0f, 1.0f);  // White color for clouds
        glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float angle = i * 60.0f;
            float x_offset = cos(angle) * 20 + x;
            float y_offset = sin(angle) * 20 + y;
            glVertex2f(x_offset, y_offset);
        }
        glEnd();
    }
    
    void drawGround() {
        glColor3f(0.2f, 0.8f, 0.2f);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 50);
        glVertex2f(0, 50);
        glEnd();
    }
    
    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        drawGround();
        drawPole();
        drawFlag();
        drawBirds();
    
        // Draw moving clouds
        for (int i = 0; i < 3; i++) {
            drawCloud(cloudX[i], 500);  // Clouds positioned at top
        }
    
        glutSwapBuffers();
    }
    
    void update(int value) {
        angle += 0.1f;
    
        // Control flag unrolling and rising
        if (flagY < 200.0f) {
            flagY += 0.5f; // Rise the flag slowly
        }
        if (flagHeight < 120.0f) {
            flagHeight += 0.5f; // Unroll the flag
        }
    
        // Control the flagpole height (for animation effect)
        if (rodHeight < 250.0f) {
            rodHeight += 0.2f;
        }
    
        // Birds flying animation
        birdX += birdSpeed;
        if (birdX > 800) birdX = -100;
    
        // Adding slight variation in bird speed for more natural movement
        birdSpeed = (sin(angle) * 0.5f) + 1.0f;
    
        // Update cloud positions
        for (int i = 0; i < 3; i++) {
            cloudX[i] += cloudSpeed[i];
            if (cloudX[i] > 800) {
                cloudX[i] = -200.0f;  // Reset cloud position
            }
        }
    
        glutPostRedisplay();
        glutTimerFunc(16, update, 0);  // Update every ~16 ms (~60 FPS)
    }
    
    void init() {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky color
        gluOrtho2D(0, 800, 0, 600);
    }
    
    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(800, 600);
        glutCreateWindow("Independence Day Flag Animation");
        init();
        glutDisplayFunc(display);
        glutTimerFunc(0, update, 0);
        glutMainLoop();
        return 0;
    }
    
}
