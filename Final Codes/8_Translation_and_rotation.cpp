#include <GL/glut.h>
#include <iostream>

using namespace std;

// Rotation angles for the cube
float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

// Function to handle keyboard inputs for rotation
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x': angleX += 5.0f; break; // Rotate around X-axis
        case 'y': angleY += 5.0f; break; // Rotate around Y-axis
        case 'z': angleZ += 5.0f; break; // Rotate around Z-axis
        case 'r': // Reset rotation
            angleX = 0.0f;
            angleY = 0.0f;
            angleZ = 0.0f;
            break;
    }
    glutPostRedisplay(); // Redraw the scene with updated angles
}

void drawCube() {
    // Front face
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply rotations
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.5f); // Move cube back to be visible
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis

    drawCube();
    glutSwapBuffers(); // Swap buffers for smooth animation
}

void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0); // Perspective projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Cube Rotation");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard handler
    glutMainLoop();
    return 0;
}
