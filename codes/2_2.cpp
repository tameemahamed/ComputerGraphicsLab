#include <GL/glut.h>
#include <cmath>

void polynomialCircle(int xc, int yc, int r) {
    glBegin(GL_POINTS);
    for (int x = -r; x <= r; x++) {
        float y = sqrt(r * r - x * x);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + x, yc - y);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    polynomialCircle(250, 250, 100);
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
    glutCreateWindow("Polynomial Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
