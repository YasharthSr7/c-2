/* Chit no. 21
Triangle with circumscibed circle
instructions:
left click using mouse to select three vertices of triangle and then right click it will draw triangle with circumscribed circle
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
        //find the determinant and multiply by 2
        double d = 2 * (p[0].xc * (p[1].yc - p[2].yc) + p[1].xc * (p[2].yc - p[0].yc) + p[2].xc * (p[0].yc - p[1].yc));

        double xi = ((pow(p[0].xc, 2) + pow(p[0].yc, 2)) * (p[1].yc - p[2].yc) +
                   (pow(p[1].xc, 2) + pow(p[1].yc, 2)) * (p[2].yc - p[0].yc) +
                   (pow(p[2].xc, 2) + pow(p[2].yc, 2)) * (p[0].yc - p[1].yc)) / d;

        double yi = ((pow(p[0].xc, 2) + pow(p[0].yc, 2)) * (p[2].xc - p[1].xc) +
                   (pow(p[1].xc, 2) + pow(p[1].yc, 2)) * (p[0].xc - p[2].xc) +
                   (pow(p[2].xc, 2) + pow(p[2].yc, 2)) * (p[1].xc - p[0].xc)) / d;

        double r = sqrt(pow((p[0].xc - xi), 2) + pow((p[0].yc - yi), 2));

        drawCircle(xi, yi, r);


        flag = false;
        glFlush();
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("triangle with inscribed circle");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return (0);
}

