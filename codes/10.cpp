#include <GL/glut.h>
#include <vector>
#include <iostream>

struct Point3D {
    float x, y, z;
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}
};

// Initial tetrahedron vertices
Point3D v0(-1.0f, -1.0f, -1.0f);
Point3D v1( 1.0f, -1.0f, -1.0f);
Point3D v2( 0.0f,  1.0f, -1.0f);
Point3D v3( 0.0f,  0.0f,  1.0f);

// Function to compute midpoint of two points
Point3D midpoint(const Point3D &p1, const Point3D &p2) {
    return Point3D((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
}

// Recursive function to draw the Sierpinski Gasket
void drawSierpinski(const Point3D &v0, const Point3D &v1, const Point3D &v2, const Point3D &v3, int depth) {
    if (depth == 0) {
        // Base case: draw the tetrahedron
        glBegin(GL_TRIANGLES);
        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v0.x, v0.y, v0.z);
        glVertex3f(v3.x, v3.y, v3.z);
        glEnd();
    } else {
        // Subdivide the tetrahedron and recurse
        Point3D m0 = midpoint(v0, v1);
        Point3D m1 = midpoint(v1, v2);
        Point3D m2 = midpoint(v2, v0);
        Point3D m3 = midpoint(v0, v3);
        Point3D m4 = midpoint(v1, v3);
        Point3D m5 = midpoint(v2, v3);

        drawSierpinski(v0, m0, m2, m3, depth - 1);
        drawSierpinski(m0, v1, m1, m4, depth - 1);
        drawSierpinski(m1, v2, m2, m5, depth - 1);
        drawSierpinski(m2, m0, v0, m3, depth - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera position
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    // Draw the 3D Sierpinski Gasket
    drawSierpinski(v0, v1, v2, v3, 3); // Change depth for more/less detail

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.33f, 1.0f, 100.0f); // 45 degrees FOV, aspect ratio 4:3, near/far planes
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Sierpinski Gasket");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
