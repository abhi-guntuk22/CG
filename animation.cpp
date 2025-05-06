#include <GL/glut.h>
#include <math.h>

float angle = 0.0f;
float birdX = -400.0f;
float flagY = 50.0f;
float cloudX = 0.0f;

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1416f * float(i) / f
        
        loat(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawFlag() {
    glPushMatrix();
    glTranslatef(400, flagY, 0); // Centered at x=400

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
    glVertex2f(400, 50);
    glVertex2f(405, 50);
    glVertex2f(405, 250); // Pole height till 250
    glVertex2f(400, 250);
    glEnd();
}

void drawBirds() {
    glColor3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 5; i++) {
        float x = birdX + i * 60;
        float y = 300 + sin(angle + i) * 10;

        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + 10, y + 10);
        glVertex2f(x + 10, y + 10);
        glVertex2f(x + 20, y);
        glEnd();
    }
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

void drawClouds() {
    glColor3f(1.0f, 1.0f, 1.0f);

    // First cloud
    drawCircle(cloudX + 100, 500, 20, 30);
    drawCircle(cloudX + 120, 510, 25, 30);
    drawCircle(cloudX + 150, 500, 20, 30);

    // Second cloud
    drawCircle(cloudX + 400, 550, 15, 30);
    drawCircle(cloudX + 420, 560, 20, 30);
    drawCircle(cloudX + 440, 550, 15, 30);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawPole();
    drawFlag();
    drawBirds();
    drawClouds();

    glutSwapBuffers();
}

void update(int value) {
    angle += 0.1f;

    // Flag rise only up to pole top
    if (flagY < 130.0f) { // 130 because 250 pole top - flag height approx (120) = 130
        flagY += 0.5f;
    }

    birdX += 1.0f;
    if (birdX > 800) birdX = -100;

    cloudX += 0.2f;
    if (cloudX > 800) cloudX = -200;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Independence Day - Flag with Clouds");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
