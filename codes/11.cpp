#include <GL/glut.h>
#include <cmath>
#include <iostream>

float t = 0.0f; // Time variable for animation

// Define the 4 control points for the flag edges (Bezier control points)
struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
};

// Control points for the flag (a simple rectangle with curved edges)
Point topLeft(0.0f, 1.0f);
Point topRight(1.0f, 1.0f);
Point bottomLeft(0.0f, -1.0f);
Point bottomRight(1.0f, -1.0f);

Point controlTopLeft(0.0f, 1.2f);     // Control point for top-left
Point controlTopRight(1.0f, 1.2f);    // Control point for top-right
Point controlBottomLeft(0.0f, -1.2f); // Control point for bottom-left
Point controlBottomRight(1.0f, -1.2f);// Control point for bottom-right

// Function to compute a point on a cubic Bezier curve
Point bezier(Point p0, Point p1, Point p2, Point p3, float t) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;
    
    float x = uuu * p0.x; // (1-t)^3 * p0.x
    x += 3 * uu * t * p1.x; // 3(1-t)^2 * t * p1.x
    x += 3 * u * tt * p2.x; // 3(1-t) * t^2 * p2.x
    x += ttt * p3.x; // t^3 * p3.x
    
    float y = uuu * p0.y;
    y += 3 * uu * t * p1.y;
    y += 3 * u * tt * p2.y;
    y += ttt * p3.y;
    
    return Point(x, y);
}

// Function to draw the flag using Bezier curves
void drawFlag() {
    glBegin(GL_LINE_STRIP);
    for (float i = 0.0f; i <= 1.0f; i += 0.01f) {
        // Top curve (top-left to top-right)
        Point p1 = bezier(topLeft, controlTopLeft, controlTopRight, topRight, i);
        // Bottom curve (bottom-left to bottom-right)
        Point p2 = bezier(bottomLeft, controlBottomLeft, controlBottomRight, bottomRight, i);
        
        // Draw the flag edges (top and bottom)
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    }
    glEnd();
}

// Function to animate the flag
void animateFlag(int value) {
    t += 0.01f;  // Increase time variable to animate the flag

    if (t > 1.0f) {
        t = 0.0f;  // Reset t if it exceeds 1
    }

    // Update the control points to animate the flag
    controlTopLeft.y = 1.2f + 0.1f * sin(t * 2 * M_PI);
    controlTopRight.y = 1.2f + 0.1f * cos(t * 2 * M_PI);
    controlBottomLeft.y = -1.2f + 0.1f * sin(t * 2 * M_PI);
    controlBottomRight.y = -1.2f + 0.1f * cos(t * 2 * M_PI);

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(16, animateFlag, 0); // Keep the animation running
}

// Function to display the flag
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, 0.0f); // Set the position of the flag
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow flag color

    drawFlag(); // Draw the flag

    glutSwapBuffers();
}

// Function to set up OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5f, 1.5f, -1.5f, 1.5f, -1.0f, 1.0f); // Set up orthogonal projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bezier Flag Animation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, animateFlag, 0); // Start animation
    glutMainLoop();
    return 0;
}
