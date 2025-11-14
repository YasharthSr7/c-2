/* Chit No.15
instructions: first left click to select center and second left click to select radius*/
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
int xc,yc,r;
bool flag=true;
// Function to implement Bresenham's circle drawing algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS);
    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc + y, yc - x);
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}


void draw(int xc,int yc,int r)
{
    // Draw the central circle
    drawCircle(xc, yc, r);
    drawCircle(xc,yc,r+40);
    // Draw the surrounding circles
    float angleIncrement = 2 * M_PI / 6;
    for (int i = 0; i < 6; ++i) {
        float angle = i * angleIncrement;
        int x = xc + (r * 2 * cos(angle));
        int y = yc + (r * 2 * sin(angle));
        drawCircle(x, y, r);
    }

    glFlush();
}
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (flag == true) {
            xc = x;
            yc = 600 - y;
            flag = false;
        } else {
            r = abs(xc - x);
            draw(xc,yc,r);
            // Set the flag to draw circles in myDisplay
            glutPostRedisplay();       // Trigger a redraw

            flag = false; // Reset flag for the next set of circles
        }
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black
  glutMouseFunc(myMouse);
 glFlush();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glPointSize(2.0); // Set point size for better visibility
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600); // Set the viewing area
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("bresenham's circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
