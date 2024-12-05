#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

vector<pair<int, int>> polygonVertices = {{100, 100}, {200, 300}, {300, 200}, {250, 50}};
int numVertices;

void scanLineFill() {
    int ymin = polygonVertices[0].second, ymax = polygonVertices[0].second;

    // Find ymin and ymax
    for (const auto& vertex : polygonVertices) {
        ymin = min(ymin, vertex.second);
        ymax = max(ymax, vertex.second);
    }

    // Fill polygon using the scan line algorithm
    for (int y = ymin; y <= ymax; y++) {
        vector<int> intersectX;

        // Find intersections of the scan line with polygon edges
        for (int i = 0; i < numVertices; i++) {
            int x1 = polygonVertices[i].first;
            int y1 = polygonVertices[i].second;
            int x2 = polygonVertices[(i + 1) % numVertices].first;
            int y2 = polygonVertices[(i + 1) % numVertices].second;

            if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
                // Calculate intersection
                int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersectX.push_back(x);
            }
        }

        // Sort intersections
        sort(intersectX.begin(), intersectX.end());

        // Draw lines between pairs of intersections
        glBegin(GL_LINES);
        for (size_t i = 0; i < intersectX.size(); i += 2) {
            glVertex2i(intersectX[i], y);
            glVertex2i(intersectX[i + 1], y);
        }
        glEnd();
    }

    glFlush();
}

// Function to draw the polygon outline
void drawPolygonOutline() {
    glBegin(GL_LINE_LOOP);
    for (const auto& vertex : polygonVertices) {
        glVertex2i(vertex.first, vertex.second);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the polygon outline
    glColor3f(0.0, 0.0, 1.0);
    drawPolygonOutline();

    // Fill the polygon
    glColor3f(1.0, 0.0, 0.0);
    scanLineFill();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    numVertices = polygonVertices.size();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Polygon Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
