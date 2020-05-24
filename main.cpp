#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
int what_to_do = 0;
int x=0,y=600;
int width = 100, height = 100, padding = 20;
int no_of_blocks = 0;
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void draw_polygon(int x, int y)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x+width, y);
        glVertex2f(x+width, y+height);
        glVertex2f(x, y+height);
    glEnd();
}

void draw_line(int x1, int y1, int x2, int y2)
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
}

void RenderString(float x, float y, char* string, void* font)
{
  char *c;

  glColor3f(1, 1, 1);
  glRasterPos2f(x, y);

  for (c = string;*c != '\0';c++)
  {
      glutBitmapCharacter(font, *c);
  }
}

void intro(int x, int y)
{
    RenderString(x, y, "Welcome to blockchain simulation", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x, y-50, "Right Click to view the menu", GLUT_BITMAP_9_BY_15);
    RenderString(x, 150, "A SIMULATION BY", GLUT_BITMAP_9_BY_15);
    RenderString(x, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(x, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);
}


void display_blocks()
{
    intro(400, 900);
    RenderString(0, y+125, "Blockchain", GLUT_BITMAP_8_BY_13);
    int tempx = 0;
    char str[3];
    if (no_of_blocks >= 9)
    {
        width = 50;
        height = 50;
        font = GLUT_BITMAP_TIMES_ROMAN_10;
    }
    if (no_of_blocks == 0)
    {
        RenderString(x, y, "No blocks! Use the menu or press 'a' to add blocks!", GLUT_BITMAP_8_BY_13);
        return;
    }
    for (int i = 1; i<= no_of_blocks; i++)
    {
        if (i <= 9)
        {
            str[0] = i + '0';
            str[1] = '\0';
        }
        else
        {
            str[0] = i/10 + '0';
            str[1] = i%10 + '0';
            str[2] = '\0';
        }
        draw_polygon(tempx, y);
        RenderString(tempx, y + (height/2),"Block",font);
        RenderString(tempx + width - 20, y + (height/2), str ,font);
        draw_line(tempx + width, y+(height/2), tempx + width + padding, y+(height/2));
        tempx = tempx + width + padding;
    }
    if (no_of_blocks <= 9)
    {
        str[0] = no_of_blocks + '0';
        str[1] = '\0';
    }
    else
    {
        str[0] = no_of_blocks/10 + '0';
        str[1] = no_of_blocks%10 + '0';
        str[2] = '\0';
    }
    RenderString(0, y - 25, "No of blocks: " , GLUT_BITMAP_8_BY_13);
    RenderString(150, y - 25, str, GLUT_BITMAP_8_BY_13);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (what_to_do == 0)
    {
        display_blocks();
    }
    if (what_to_do == 1)
    {
       x = x + width + padding;
       no_of_blocks += 1;
       display_blocks();
       what_to_do = 0;
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

void blockchain_menu(int option)
{
    if (option == 1)
    {
        what_to_do = 1;
    }
    else
    {
        what_to_do = 2;
    }
}

void keys(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        what_to_do = 1;
    }
    display();
}


void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Blockchain Simulation");

    init();
    glutDisplayFunc(display);

    glutCreateMenu(blockchain_menu);
    glutAddMenuEntry("1.Add a block(Key a)", 1);
    glutAddMenuEntry("2.Display block", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keys);

    glutMainLoop();
}
