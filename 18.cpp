/* Chit no. 18
five concentric circle
instructions: first left click to select center and second left click to select radius
*/
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;
bool flag = true;
int xc, yc, r;
bool draw_circles_flag = false; // New flag to control circle drawing

void displayPoint(int x, int y) {
    glColor3f(0, 0, 1);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void SimpleLine(float x1, float y1, float x2, float y2) {
    float step;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    float Xinc = dx / step;
    float Yinc = dy / step;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= step; i++) {
        displayPoint(round(x), round(y)); // Use round to get integer coordinates
        x = x + Xinc;
        y = y + Yinc;
    }
}

void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int p = 3 - 2 * radius;
    glPointSize(1);
    glBegin(GL_POINTS); // Begin drawing points for the circle
    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc + y, yc - x);
        if (p < 0) {
            x++;
            p = p + 4 * x + 6;
        } else {
            x++;
            y--;
            p = p + 4 * (x - y) + 10;
        }
    }
    glEnd(); // End drawing points for the circle
}

void drawCircles(int xc, int yc, int r) {
    glColor3f(0.0f, 0.0f, 0.0f);
    SimpleLine(0, 300, 600, 300);
    SimpleLine(300, 0, 300, 600);
    for (int i = 0; i < 5; i++) {
        drawCircle(xc, yc, r + i * 20);
    }
}

void myDisplay() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    SimpleLine(0, 300, 600, 300);
    SimpleLine(300, 0, 300, 600);

    if (draw_circles_flag) {
        drawCircles(xc, yc, r);
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
            draw_circles_flag = true; // Set the flag to draw circles in myDisplay
            glutPostRedisplay();       // Trigger a redraw
            cout << xc << " " << yc << " " << r << endl;
            flag = true; // Reset flag for the next set of circles
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Five Concentric Circles");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}
