#include <GL/glut.h>
#include <iostream>

using namespace std;

// Current projection type: 0 for orthographic, 1 for perspective
int projectionType = 0;

// Function to draw the cube
void drawCube() {
    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);

    // Back face
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);

    // Top face
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);

    // Bottom face
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f(-0.5, -0.5,  0.5);

    // Right face
    glColor3f(1.0, 0.0, 1.0); // Magenta
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5, -0.5,  0.5);

    // Left face
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f(-0.5,  0.5, -0.5);

    glEnd();
}

// Function to set orthographic projection
void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to set perspective projection
void setPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move the cube back for visibility
    if (projectionType == 1) {
        glTranslatef(0.0, 0.0, -5.0);
    }

    // Rotate the cube for a better view
    glRotatef(30.0, 1.0, 1.0, 0.0);

    drawCube();
    glutSwapBuffers();
}

// Keyboard handler to toggle projections
void keyboard(unsigned char key, int x, int y) {
    if (key == 'p') {
        projectionType = 1; // Perspective
        setPerspectiveProjection();
    } else if (key == 'o') {
        projectionType = 0; // Orthographic
        setOrthographicProjection();
    }
    glutPostRedisplay(); // Redraw with new projection
}

// Initialization
void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    setOrthographicProjection(); // Start with orthographic projection
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube Projection");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
