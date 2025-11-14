#include <GL/glut.h>
#include <iostream>

using namespace std;

int ch;
float intCol[3] = {1.0, 1.0, 1.0};      // Interior color (white)
float fillColf[3] = {1.0, 0.0, 0.0};    // Flood Fill color (red)
float fillColb[3] = {0.0, 0.0, 1.0};    // Boundary Fill color (blue)
float borderColor[3] = {1.0, 0.0, 0.0}; // Boundary color (red) - must match 'b' key polygon color

void setPixel(int pointx, int pointy, float f[3])
{
    // This code block was outside the function in the original file
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void drawPolygon(int x1, int y1, int x2, int y2)
{
    // Corrected the misplaced brace from the original file
    glColor3f(0.0, 0.0, 0.0); // Draw in black for flood fill
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    glFlush();
}

void display()
{
    // Flushes the buffer
    glFlush();
}

void floodfill4(int x, int y, float oldcolor[3], float newcolor[3])
{
    // This code was outside the function in the original file
    float color[3];
    // Read pixel data
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color); // Corrected 1.0 to 1

    // Corrected = (assignment) to == (comparison)
    if (color[0] == oldcolor[0] && color[1] == oldcolor[1] && color[2] == oldcolor[2])
    {
        // Code was outside the if-block in the original
        setPixel(x, y, newcolor);
        floodfill4(x + 1, y, oldcolor, newcolor);
        floodfill4(x - 1, y, oldcolor, newcolor);
        floodfill4(x, y + 1, oldcolor, newcolor);
        floodfill4(x, y - 1, oldcolor, newcolor);
    }
}

void boundaryFill4(int x, int y, float fillColor[3], float border[3])
{
    float interiorColor[3];
    // Corrected "glRead Pixels" to "glReadPixels" and 1.0 to 1
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorColor);

    // Corrected "!= " to "!=" and fixed mismatched braces
    if ((interiorColor[0] != border[0] || interiorColor[1] != border[1] || interiorColor[2] != border[2]) &&
        (interiorColor[0] != fillColor[0] || interiorColor[1] != fillColor[1] || interiorColor[2] != fillColor[2]))
    {
        setPixel(x, y, fillColor);
        boundaryFill4(x + 1, y, fillColor, border);
        boundaryFill4(x - 1, y, fillColor, border);
        boundaryFill4(x, y + 1, fillColor, border);
        boundaryFill4(x, y - 1, fillColor, border);
        
        // Kept the 8-way fill from the original, but fixed typos
        boundaryFill4(x + 1, y + 1, fillColor, border);
        boundaryFill4(x - 1, y - 1, fillColor, border);
        boundaryFill4(x - 1, y + 1, fillColor, border);
        boundaryFill4(x + 1, y - 1, fillColor, border); // Fixed y+11 typo
    }
}

void mouse(int btn, int state, int x, int y)
{
    // Corrected brace issues
    // Corrected btn-GLUT... to btn == GLUT...
    // Corrected state = GLUT... to state == GLUT...
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xi = x;
        int yi = 600 - y; // y is inverted in GLUT

        // Corrected ch=1 to ch == 1
        if (ch == 1)
        {
            floodfill4(xi, yi, intCol, fillColf);
        }
        // Corrected ch=2 to ch == 2
        if (ch == 2)
        {
            // Note: For boundary fill, the 'borderColor' global must
            // match the color the polygon was drawn with (red, in case 'b')
            boundaryFill4(xi, yi, fillColb, borderColor);
        }
    }
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    // Corrected dot '.' to '{'
    // Corrected extra braces
    switch (key)
    {
    case 'f':
        ch = 1;
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        drawPolygon(150, 250, 300, 440); // Draws a black-bordered polygon
        glutMouseFunc(mouse);
        break; // Added missing 'break'
    case 'b':
        ch = 2;
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0); // Draw red polygon (matches global borderColor)
        glBegin(GL_LINE_LOOP);
        glVertex2i(200, 200);
        glVertex2i(400, 200);
        glVertex2i(300, 400);
        glVertex2i(250, 300);
        glVertex2i(220, 400);
        glEnd();
        glFlush(); // Added flush after drawing
        glutMouseFunc(mouse);
        break;
    }
    glutPostRedisplay();
}

void myinit()
{
    // Code was outside the function in the original
    gluOrtho2D(0, 600, 0, 600);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Flood-Fill and Boundary-Fill");
    
    // Corrected "cout<<<" to "cout <<"
    cout << "\n f: flood fill algorithm";
    cout << "\n b: boundary fill algorithm\n";
    
    myinit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}