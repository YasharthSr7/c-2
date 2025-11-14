// Chit No.17 and Chit No.13

/* Program to display house using bresenham's line and bresenham's circle algorithm
Instructions: press l using keyboard  to draw lines continue to  left click to draw house , right click if you complete part of house again start another part by left clicks
after you draw all lines of house then press c using keyboard to draw circle then left click to select circle and again left click to select radius
To display Man: Follow same instructions
*/
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
void displayPoint(int x, int y)
{
    glColor3f(0, 1, 0);
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
float x01, x2, y01, y2;
int ch,xc,yc,r;
int flag=true;

void SimpleLine(float x1, float y1, float x2, float y2) {
    float dx, dy, p;
    int i;
    float incx, incy, inc1, inc2;
    float x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    if (dx < 0)
    {
        dx = -dx;
    }
    if (dy < 0)
    {
        dy = -dy;
    }
    incx = 1;
    if (x2 < x1)
    {
        incx = -1;
    }
    incy = 1;
    if (y2 < y1)
    {
        incy = -1;
    }
    x = x1;
    y = y1;
    if (dx > dy)
    {
        displayPoint(x, y);
        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                x =x+incx;
                y = y+ incy;
                p =p+ inc1;
            }
            else
            {
                x =x+incx;
                p =p+ inc2;
            }
            displayPoint(x, y);
        }
    }
    else
    {
        displayPoint(x, y);
        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x =x+ incx;
                y =y+ incy;
                p =p+ inc1;
            }
            else
            {
                p=p+inc2;
                y =y+ incy;
            }
            displayPoint(x, y);
        }
    }
    glFlush();
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
void myMouse(int button, int state, int x, int y)
{
    static int xst, yst, pt = 0;


        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if(ch==1)
            {

                if (pt == 0)
                {
                    xst = x;
                    yst = 600-y;

                    pt = pt + 1;
                }
                else
                {



                    SimpleLine(xst, yst, x, 600-y);


                    xst = x;
                    yst = 600-y;

            }
            }
            if(ch==2 && flag==true)
            {
                xc=x;
                yc=600-y;
                flag=false;

            }
            else if(ch==2 && flag==false)
            {
                r=abs(xc-x);
                drawCircle(xc,yc,r);
                flag=true;
            }

    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        pt = 0;

    }
//Clear Screen
        glFlush();
}
void keyboard(unsigned char key,int x,int y)
{
    if(key=='l')//press l for line
    {
        ch=1;
        glutMouseFunc(myMouse);
    }
    if(key=='c')//press c for circle
    {

        ch=2;
        glutMouseFunc(myMouse);
    }

}
void initialize(void)
{
glClearColor(1.0, 1.0, 1.0, 1.0);
glClear(GL_COLOR_BUFFER_BIT);
// gluOrtho2D(l,r,b,t)
gluOrtho2D(0, 600, 0, 600);
}
void primitives(void)
{
//glClearColor(1.0, 1.0, 1.0, 1.0);
//glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1, 0, 0);

glutKeyboardFunc(keyboard);
}

int main(int argc,char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE);
 glutInitWindowPosition(0, 0);
 glutInitWindowSize(600, 600);
 glutCreateWindow("OpenGL - Bresenham's Algorithm to draw house");
 initialize();

 glutDisplayFunc(primitives);
 glutMainLoop();
 return 0;
}


