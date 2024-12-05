#include <GL/glut.h>
#include <iostream>

using namespace std;

// Number of recursive subdivisions
int recursionLevel = 3;

// Vertices of the initial tetrahedron
GLfloat vertices[4][3] = {
    {0.0, 0.0, 1.0},        // Vertex 0
    {0.0, 0.9428, -0.3333}, // Vertex 1
    {-0.8165, -0.4714, -0.3333}, // Vertex 2
    {0.8165, -0.4714, -0.3333}   // Vertex 3
};

// Function to draw a triangle
void drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3) {
    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

// Recursive function to subdivide the tetrahedron
void divideTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3, int level) {
    if (level == 0) {
        drawTriangle(v1, v2, v3); // Base case: Draw triangle
    } else {
        GLfloat mid[3][3];
        for (int i = 0; i < 3; i++) {
            mid[0][i] = (v1[i] + v2[i]) / 2.0; // Midpoint of v1 and v2
            mid[1][i] = (v2[i] + v3[i]) / 2.0; // Midpoint of v2 and v3
            mid[2][i] = (v3[i] + v1[i]) / 2.0; // Midpoint of v3 and v1
        }
        // Recursive subdivision
        divideTriangle(v1, mid[0], mid[2], level - 1);
        divideTriangle(mid[0], v2, mid[1], level - 1);
        divideTriangle(mid[2], mid[1], v3, level - 1);
    }
}

// Function to draw a tetrahedron by subdividing each triangular face
void divideTetrahedron(GLfloat* v0, GLfloat* v1, GLfloat* v2, GLfloat* v3, int level) {
    glColor3f(1.0, 0.0, 0.0); // Red for one face
    divideTriangle(v0, v1, v2, level);

    glColor3f(0.0, 1.0, 0.0); // Green for another face
    divideTriangle(v0, v2, v3, level);

    glColor3f(0.0, 0.0, 1.0); // Blue for another face
    divideTriangle(v0, v3, v1, level);

    glColor3f(1.0, 1.0, 0.0); // Yellow for the last face
    divideTriangle(v1, v2, v3, level);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.5); // Move back for better visibility
    divideTetrahedron(vertices[0], vertices[1], vertices[2], vertices[3], recursionLevel);
    glutSwapBuffers();
}

// Keyboard callback to adjust recursion level
void keyboard(unsigned char key, int x, int y) {
    if (key == '+') {
        recursionLevel++;
    } else if (key == '-' && recursionLevel > 0) {
        recursionLevel--;
    }
    glutPostRedisplay(); // Redraw with new recursion level
}

// Initialization function
void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Sierpinski Gasket");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
