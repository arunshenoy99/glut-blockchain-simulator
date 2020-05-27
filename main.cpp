#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
//Declaring global variables

int what_to_do = 0;
int x=0,y=600,block_width = 100, block_height = 100;
int padding = 20;
int open_transaction_width = 100, open_transaction_height = 100;
int no_of_blocks = 1, no_of_ot = 0;
int transactions[100];
int clicked_block = 0, clicked_ot = 0;

//Declaring fonts for display

void *block_font = GLUT_BITMAP_TIMES_ROMAN_24;
void *open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_24;


//Draw block or open transaction

void draw_polygon(int x, int y, int width, int height)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x+width, y);
        glVertex2f(x+width, y+height);
        glVertex2f(x, y+height);
    glEnd();
}

//Draw connections between blocks

void draw_line(int x1, int y1, int x2, int y2)
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
}

//Render bitmap characters

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

void to_string_digit(char str[], int digit)
{
    str[0] = digit + '0';
    str[1] = '\0';
}

void to_string_digits(char str[], int digits)
{
    str[0] = digits/10 + '0';
    str[1] = digits%10 + '0';
    str[2] = '\0';
}

//Introduction and our names

void intro(int x, int y)
{
    RenderString(x, y, "Welcome to Blockchain Simulator", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x, y-50, "Right Click to view the menu", GLUT_BITMAP_9_BY_15);
    RenderString(x, 150, "A SIMULATION BY", GLUT_BITMAP_9_BY_15);
    RenderString(x, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(x, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);
}


//Display blockchain

void display_blocks()
{
    int tempx = 0;
    char str[3];

    RenderString(0, y+125, "Blockchain(Click on any block to view it's contents)", GLUT_BITMAP_8_BY_13);

    if (no_of_blocks >= 9)
    {
        block_width = 50;
        block_height = 100;
        block_font = GLUT_BITMAP_TIMES_ROMAN_10;
    }


    for (int i = 1; i<= no_of_blocks; i++)
    {
        if (i <= 9)
        {
            to_string_digit(str, i);
        }
        else
        {
            to_string_digits(str, i);
        }
        draw_polygon(tempx, y, block_width, block_height);
        if (i == 1)
        {
            RenderString(tempx, y + (block_height/2), "Genesis Block", block_font);
        }
        else
        {
            RenderString(tempx, y + (block_height/2), "Block", block_font);
            RenderString(tempx + block_width - 20, y + (block_height/2), str ,block_font);
        }
        draw_line(tempx + block_width, y+(block_height/2), tempx + block_width + padding, y+(block_height/2));
        tempx = tempx + block_width + padding;
    }

    if (no_of_blocks <= 9)
    {
        to_string_digit(str, no_of_blocks);
    }
    else
    {
        to_string_digits(str, no_of_blocks);
    }

    RenderString(0, y - 25, "No of blocks: " , GLUT_BITMAP_8_BY_13);
    RenderString(150, y - 25, str, GLUT_BITMAP_8_BY_13);
}

//Display open transactions

void display_open_transactions()
{
    int oty = y - 300;
    RenderString(0, oty + 125, "Open Transactions", GLUT_BITMAP_8_BY_13);
    int tempx = 0;
    char str[3];
    if (no_of_ot >= 9)
    {
        open_transaction_width = 50;
        open_transaction_height = 100;
        open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_10;
    }
    if (no_of_ot == 0)
    {
        RenderString(0, oty + 100 , "No open transactions! Use the menu or press 't' to add a transaction!", GLUT_BITMAP_8_BY_13);
        return;
    }
    for (int i = 1; i<= no_of_ot; i++)
    {
        if (i <= 9)
        {
            to_string_digit(str, i);
        }
        else
        {
            to_string_digits(str, i);
        }
        draw_polygon(tempx, oty, open_transaction_width, open_transaction_height);
        RenderString(tempx, oty + (open_transaction_height/2), "Transaction", open_transaction_font);
        RenderString(tempx + open_transaction_width - 10, oty + (open_transaction_height/2), str ,open_transaction_font);
        tempx = tempx + open_transaction_width + padding;
    }
    if (no_of_ot <= 9)
    {
        to_string_digit(str, no_of_ot);
    }
    else
    {
        to_string_digits(str, no_of_ot);
    }
    RenderString(0, oty - 25, "No of open transactions: " , GLUT_BITMAP_8_BY_13);
    RenderString(150, oty - 25, str, GLUT_BITMAP_8_BY_13);

}

void display_block()
{
    char block[3];
    char previous_block[3];
    char t[3];
    draw_polygon(300, 500, 300, 300);

    if (clicked_block <= 9)
    {
        to_string_digit(block, clicked_block);
        to_string_digit(previous_block, clicked_block - 1);
    }
    else
    {
        to_string_digits(block, clicked_block);
        if ((clicked_block - 1) == 9)
        {
            to_string_digit(previous_block, clicked_block - 1);
        }
        else
        {
            to_string_digits(previous_block, clicked_block - 1);
        }
    }
    if (transactions[clicked_block] <= 9)
    {
        to_string_digit(t, transactions[clicked_block]);
    }
    else
    {
        to_string_digits(t, transactions[clicked_block]);
    }
    RenderString(325, 750, "Index: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(375, 750, block, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(325, 725, "Previous Hash: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(425, 725, previous_block, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(325, 700, "Transactions: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(425, 700, t, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(300, 475, "Press B to go back !", GLUT_BITMAP_8_BY_13);
}

//Add a new block

void add_block()
{

    x = x + block_width + padding;
    no_of_blocks += 1;
    transactions[no_of_blocks] = no_of_ot;
    no_of_ot = 0;
    open_transaction_width = 100;
    open_transaction_height = 100;
    open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_24;
}


//Display function called again and again

void display()
{
    glutFullScreen();
    glClear(GL_COLOR_BUFFER_BIT);

    intro(400, 900);

    if (what_to_do == 0)
    {
        display_blocks();
        display_open_transactions();
    }
    if (what_to_do == 1)
    {
        add_block();
        display_blocks();
        what_to_do = 0;
    }
    if (what_to_do == 2)
    {
        x = x + open_transaction_width + padding;
        no_of_ot += 1;
        display_blocks();
        display_open_transactions();
        what_to_do = 0;

    }
    if (what_to_do == 3)
    {
        for (int i = 1; i <= no_of_blocks; i++)
        {
            transactions[i] = 0;
        }
        no_of_blocks = 1;
        no_of_ot = 0;
        block_width = 100;
        block_height = 100;
        open_transaction_width = 100;
        open_transaction_height = 100;
        block_font = GLUT_BITMAP_TIMES_ROMAN_24;
        open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_24;
        what_to_do = 0;
    }
    if (what_to_do == 4)
    {
        int win = glutGetWindow();
        glutDestroyWindow(win);
        return;
    }
    if (what_to_do == 5)
    {
        if (clicked_block > no_of_blocks)
        {
            display_blocks();
            display_open_transactions();
            what_to_do = 0;
        }
        else
        {
            display_block();
        }
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

//Right clicking menu

void blockchain_menu(int option)
{
    if (option == 1)
    {
        what_to_do = 1;
    }
    if (option == 2)
    {
        what_to_do = 2;
    }
    if (option == 3)
    {
        what_to_do = 3;
    }
    if (option == 4)
    {
        what_to_do = 4;
    }
}

//Keyboard listener

void keys(unsigned char key, int x, int y)
{
    if (key == 'm')
    {
        what_to_do = 1;
    }
    if (key == 't')
    {
        what_to_do = 2;
    }
    if (key == 'r')
    {
        what_to_do = 3;
    }
    if ((int)key == 27)
    {
        what_to_do = 4;
    }
    if (key == 'b')
    {
        what_to_do = 0;
    }
    display();
}

//Mouse Listener
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && y >= 1000 - (::y + block_height) && y <= 1000 - ::y )
    {
       if (no_of_blocks < 9)
       {
            clicked_block = ((x) / (184)) + 1;
            what_to_do = 5;
       }
       else
       {
            clicked_block = ((x) / (105)) + 1;
            what_to_do = 5;
       }
    }
}


//Initialize graphics system

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

    glutInitWindowPosition(0, 0);
    glutCreateWindow("BLOCKCHAIN SIMULATION");

    init();
    glutDisplayFunc(display);

    glutCreateMenu(blockchain_menu);
    glutAddMenuEntry("1. Mine a block(Key m)", 1);
    glutAddMenuEntry("2. Add a transaction(Key t)", 2);
    glutAddMenuEntry("3. Reset(Key r)", 3);
    glutAddMenuEntry("4. Exit Simulation(Key Esc)", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);

    glutMainLoop();
}
