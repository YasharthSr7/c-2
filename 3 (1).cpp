/* Chit no. 3
Triangle with inscribed circle
instructions:
left click using mouse to select three vertices of triangle and then right click it will draw triangle with inscribed circle
*/
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
int angle;
int px, py;
void displayPoint(int x, int y)
{
   glColor3f(0, 0, 1);
   glPointSize(2);
   glBegin(GL_POINTS);
   glVertex2i(x, y);
   glEnd();
}


void SimpleLine(float x1, float y1, float x2, float  y2)
{
   float step;

   float dx = x2 - x1;
   float dy = y2 - y1;

   if (abs(dx) > abs(dy))
   {
      step = abs(dx);
   }
   else
      step = abs(dy);

   float Xinc = dx / step;
   float Yinc = dy / step;
   float x = x1;
   float y = y1;

   for (int i = 0; i <= step; i++)
   {
      displayPoint(x, y);
      x = x + Xinc;
      y = y + Yinc;
   }
   glFlush();
}
void drawCircle(int xc,int yc,int radius)
{
    int x=0;
    int y=radius;

    int p=3-2*radius;
    while(x<=y)
    {
        glBegin(GL_POINTS);
        glVertex2i(xc+x,yc+y);
        glVertex2i(xc+y,yc+x);
        glVertex2i(xc-x,yc+y);
        glVertex2i(xc-y,yc+x);
        glVertex2i(xc-x,yc-y);
        glVertex2i(xc-y,yc-x);
        glVertex2i(xc+x,yc-y);
        glVertex2i(xc+y,yc-x);
        glEnd();
        if(p<0)
        {
            x++;
            p=p+4*x+6;
        }
        if(p>=0)
        {
            x++;
            y--;
            p=p+4*(x-y)+10;
        }

    }
    glFlush();
}

void drawPolygon(struct Point p[], int n) {
    glPointSize(1.0);
int j;
    for ( j = 0; j < n-1; j++) {
       SimpleLine(p[j].xc,p[j].yc,p[j+1].xc,p[j+1].yc);
    }
    SimpleLine(p[j].xc,p[j].yc,p[0].xc,p[0].yc);
    glEnd();
    glFlush();
}

void myDisplay() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

}
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (flag == true) {
            p[i].xc = x;
            p[i].yc = 600 - y;
            i++;
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        n = i;
        drawPolygon(p, n);
        //find the length of sides of traingle
        double a = sqrt(pow((p[2].xc - p[1].xc), 2.0) + pow((p[2].yc - p[1].yc), 2.0));
        double b = sqrt(pow((p[2].xc - p[0].xc), 2.0) + pow((p[2].yc - p[0].yc), 2.0));
        double c = sqrt(pow((p[1].xc - p[0].xc), 2.0) + pow((p[1].yc - p[0].yc), 2.0));
        //center of circle
        double xi = (double)(a * p[0].xc + b * p[1].xc + c * p[2].xc) / (a + b + c);
        double yi = (double)(a * p[0].yc + b * p[1].yc + c * p[2].yc) / (a + b + c);
        //semiperimeter
        double s = (a + b + c) / 2.0;
        //area of triangle
        double k = 0.5 * abs(p[0].xc * (p[1].yc - p[2].yc) + p[1].xc * (p[2].yc - p[0].yc) + p[2].xc * (p[0].yc - p[1].yc));
        //radius
        double r = k / s;
        drawCircle(xi, yi, r);
        cout << xi << " " << yi << " " << r << endl;

        flag = false;
        glFlush();
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("triangle with circumscribed circle");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}

