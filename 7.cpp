//left click to select vertices of polygon , after that right click and choose option to proceed
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Point {
    int xc;
    int yc;
} p[10];
int i = 0;
int n;

bool flag = true;
int tx, ty, sx, sy;
struct Point translated_p[10];
struct Point scaled_p[10];
bool translated = false;
bool scaled = false;

void displayPoint(int x, int y) {
    glColor3f(0, 0, 1);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void SimpleLine(float x1, float y1, float x2, float  y2) {
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

    for (int j = 0; j <= step; j++) {
        displayPoint(round(x), round(y));
        x = x + Xinc;
        y = y + Yinc;
    }
    glFlush();
}

void drawPolygon(struct Point points[], int num_points){
   
    glPointSize(1.0);
    int j;
    for (j = 0; j < num_points - 1; j++) {
        SimpleLine(points[j].xc, points[j].yc, points[j + 1].xc, points[j + 1].yc);
    }
    
        SimpleLine(points[j].xc, points[j].yc, points[0].xc, points[0].yc);
    
    glEnd();
    glFlush();
}

void myDisplay() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    SimpleLine(0, 300, 600, 300);
    SimpleLine(300, 0, 300, 600);

    if (!flag && n > 0) {
        drawPolygon(p, n); // Draw original 

        if (translated) {
            drawPolygon(translated_p, n);// draw translated polygon
        }
        if (scaled) {
            drawPolygon(scaled_p, n); // draw scaled polygon
        }
    }
    glFlush();
}

void translate(int tx, int ty) {
    for (int j = 0; j < n; j++) {
        translated_p[j].xc = p[j].xc + tx;
        translated_p[j].yc = p[j].yc + ty;
    }
    translated = true;
    glutPostRedisplay();
}

void scaling(int sx, int sy) {
    for (int j = 0; j < n; j++) {
        scaled_p[j].xc = round(p[j].xc * sx);
        scaled_p[j].yc = round(p[j].yc * sy);
    }
    scaled = true;
    glutPostRedisplay();
}

void menu(int choice) {
    switch (choice) {
    case 1: // Translate
        cout << "\n enter tx and ty: ";
        cin >> tx >> ty;
        translate(tx, ty);
        break;
    case 2: // Scaling
        cout << "\n enter sx and sy: ";
        cin >> sx >> sy;
        scaling(sx, sy);
        break;
    case 3:
        exit(0);
    }
    glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (flag == true && i < 10) {
            p[i].xc = x;
            p[i].yc = 600 - y;
            displayPoint(x, 600 - y);
            i++;
            glFlush();
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (flag == true && i >= 3) {
            n = i;
            // Initialize translated and scaled polygons with the original
            for (int j = 0; j < n; j++) {
                translated_p[j] = p[j];
                scaled_p[j] = p[j];
            }
            drawPolygon(p, n); // Draw the initial polygon
            flag = false;
            translated = false; // Reset transformation flags
            scaled = false;
            glutCreateMenu(menu);
            glutAddMenuEntry("1. Translate", 1);
            glutAddMenuEntry("2. Scaling", 2);
            glutAddMenuEntry("3. Exit", 3);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
        } else if (flag == true) {
            cout << "Please select at least 3 vertices to form a polygon." << endl;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Original and Transformed Polygon");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}
