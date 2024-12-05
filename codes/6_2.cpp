#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Pivot point
float pivotX = 250, pivotY = 250;

// Rotation angle (in degrees)
float angle = 0.0;

// Function to rotate a point around a pivot
void rotatePoint(float& x, float& y, float pivotX, float pivotY, float angle) {
    float radian = angle * M_PI / 180.0;
    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    // Translate point to origin
    float translatedX = x - pivotX;
    float translatedY = y - pivotY;

    // Rotate
    float rotatedX = translatedX * cosTheta - translatedY * sinTheta;
    float rotatedY = translatedX * sinTheta + translatedY * cosTheta;

    // Translate back to pivot
    x = rotatedX + pivotX;
    y = rotatedY + pivotY;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw pivot point
    glColor3f(1.0, 0.0, 0.0); // Red
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(pivotX, pivotY);
    glEnd();

    // Triangle vertices
    float x1 = 200, y1 = 200, x2 = 300, y2 = 400, x3 = 400, y3 = 200;

    // Rotate points
    rotatePoint(x1, y1, pivotX, pivotY, angle);
    rotatePoint(x2, y2, pivotX, pivotY, angle);
    rotatePoint(x3, y3, pivotX, pivotY, angle);

    // Draw triangle
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();

    glFlush();
}

// Timer function to update the rotation
void timer(int value) {
    angle += 1.0; // Increment rotation angle
    if (angle >= 360) {
        angle -= 360; // Keep angle within 0-360 range
    }
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, timer, 0); // Call timer function again after 16ms (~60 FPS)
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
    glutCreateWindow("Rotate Triangle Around Pivot Point");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0); // Start the timer for continuous rotation
    glutMainLoop();
    return 0;
}
