#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Center of magnification
float centerX = 250, centerY = 250;

// Rectangle vertices
float xA = 150, yA = 150, xB = 350, yB = 150, xC = 350, yC = 300, xD = 150, yD = 300;

// Scaling factor
float scale = 1.0;

// Function to magnify a point
void magnifyPoint(float& x, float& y, float cx, float cy, float scale) {
    x = cx + scale * (x - cx);
    y = cy + scale * (y - cy);
}

void magnifyRectangle() {
    float mxA = xA, myA = yA;
    float mxB = xB, myB = yB;
    float mxC = xC, myC = yC;
    float mxD = xD, myD = yD;

    // Apply magnification
    magnifyPoint(mxA, myA, centerX, centerY, scale);
    magnifyPoint(mxB, myB, centerX, centerY, scale);
    magnifyPoint(mxC, myC, centerX, centerY, scale);
    magnifyPoint(mxD, myD, centerX, centerY, scale);

    // Draw the magnified rectangle
    glBegin(GL_QUADS);
    glVertex2f(mxA, myA);
    glVertex2f(mxB, myB);
    glVertex2f(mxC, myC);
    glVertex2f(mxD, myD);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the reference point
    glColor3f(1.0, 0.0, 0.0); // Red
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(centerX, centerY);
    glEnd();

    // Draw magnified rectangle
    glColor3f(1.0, 1.0, 0.0); // Yellow
    magnifyRectangle();

    glFlush();
}

// Timer function to increase scaling
void timer(int value) {
    scale += 0.05; // Increment scaling factor
    if (scale > 2.0) scale = 1.0; // Reset scaling after magnification
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(50, timer, 0);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Magnify Rectangle");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
