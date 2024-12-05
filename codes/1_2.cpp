#include <GL/glut.h>
#include <cmath>

void ddaLine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1, y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y);
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    ddaLine(50, 50, 450, 300);
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
    glutCreateWindow("DDA Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
