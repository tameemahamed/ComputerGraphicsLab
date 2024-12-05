#include <GL/glut.h>
#include <cmath>

void trigonometricCircle(int xc, int yc, int r) {
    glBegin(GL_POINTS);
    for (float angle = 0; angle <= 360; angle += 0.1) {
        float x = r * cos(angle * M_PI / 180);
        float y = r * sin(angle * M_PI / 180);
        glVertex2i(xc + x, yc + y);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    trigonometricCircle(250, 250, 100);
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
    glutCreateWindow("Trigonometric Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
