#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Center of magnification
float centerX = 250, centerY = 250;

// Circle parameters
float circleX = 250, circleY = 250, radius = 50;

// Scaling factor
float scale = 1.0;

void magnifyCircle() {
    float magnifiedRadius = radius * scale;

    // Draw the magnified circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float radian = i * M_PI / 180.0;
        float x = circleX + magnifiedRadius * cos(radian);
        float y = circleY + magnifiedRadius * sin(radian);
        glVertex2f(x, y);
    }
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

    // Draw magnified circle
    glColor3f(0.0, 1.0, 0.0); // Green
    magnifyCircle();

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
    glutCreateWindow("Magnify Circle");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
