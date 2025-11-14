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
int tx, ty;
int angle;
int px, py;

struct Point translated_p[10];
struct Point rotated_origin_p[10];
struct Point rotated_point_p[10];

bool translated = false;
bool rotated_origin = false;
bool rotated_point = false;

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

void drawPolygon(struct Point points[], int num_points) {
   
    glPointSize(1.0);
    int j;
    for (j = 0; j < num_points - 1; j++) {
        SimpleLine(points[j].xc, points[j].yc, points[j + 1].xc, points[j + 1].yc);
    }
    if (num_points > 0) {
        SimpleLine(points[j].xc, points[j].yc, points[0].xc, points[0].yc);
    }
    glEnd();
    glFlush();
}

void myDisplay() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(300, 0);
    glVertex2i(300, 600);
    glVertex2i(0, 300);
    glVertex2i(600, 300);
    glEnd();

    if (!flag && n > 0) {
        drawPolygon(p, n); 

        if (translated) {
            drawPolygon(translated_p, n); 
        }
        if (rotated_origin) {
            drawPolygon(rotated_origin_p, n); 
            }
        if (rotated_point) {
            drawPolygon(rotated_point_p, n);
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

void rotation1(int angle) {
    float ang = angle * 3.14 / 180.0;
    for (int j = 0; j < n; j++) {
        rotated_origin_p[j].xc = round(p[j].xc * cos(ang) - p[j].yc * sin(ang));
        rotated_origin_p[j].yc = round(p[j].xc * sin(ang) + p[j].yc * cos(ang));
    }
    rotated_origin = true;
    glutPostRedisplay();
}

void rotation2(int angle, int px, int py) {
    float ang = angle * 3.14 / 180.0;
    for (int j = 0; j < n; j++) {
        float temp_x = p[j].xc - px;
        float temp_y = p[j].yc - py;
        rotated_point_p[j].xc = round(temp_x * cos(ang) - temp_y * sin(ang) + px);
        rotated_point_p[j].yc = round(temp_x * sin(ang) + temp_y * cos(ang) + py);
    }
    rotated_point = true;
    glutPostRedisplay();
}

void menu(int choice) {
    switch (choice) {
    case 1: // Translate
        cout << "\n enter tx and ty: ";
        cin >> tx >> ty;
        translate(tx, ty);
        break;
    case 2: // Rotation about origin
        cout << "\n enter angle: ";
        cin >> angle;
        rotation1(angle);
        break;
    case 3: // Rotation about point
        cout << "\n enter angle: ";
        cin >> angle;
        cout << "\n enter px and py: ";
        cin >> px >> py;
        rotation2(angle, px, py);
        break;
    case 4:
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
            // Initialize transformed polygons
            for (int j = 0; j < n; j++) {
                translated_p[j] = p[j];
                rotated_origin_p[j] = p[j];
                rotated_point_p[j] = p[j];
            }
            drawPolygon(p, n); // Draw initial polygon
            flag = false;
            translated = false;
            rotated_origin = false;
            rotated_point = false;
            glutCreateMenu(menu);
            glutAddMenuEntry("1. Translate", 1);
            glutAddMenuEntry("2. Rotation about origin", 2);
            glutAddMenuEntry("3. Rotation about point", 3);
            glutAddMenuEntry("4. Exit", 4);
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
    glutCreateWindow("Polygon Translation and Rotation");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}
