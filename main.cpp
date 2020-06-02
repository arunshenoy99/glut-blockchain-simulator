#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
//Declaring global variables

int what_to_do = -1;
int x=0,y=600,block_width = 100, block_height = 100;
int padding = 20;
int open_transaction_width = 100, open_transaction_height = 100;
int no_of_blocks = 1, no_of_ot = 0;
int transactions[100];
int clicked_block = 0, clicked_ot = 0, manip_block = -2, temp_transac = 0;
unsigned int d = 0;

//Declaring fonts for display

void *block_font = GLUT_BITMAP_TIMES_ROMAN_24;
void *open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_24;


//Draw block or open transaction

void draw_polygon(int x, int y, int width, int height, float r = 1.0, float g = 0.0, float b = 0.0)
{
    glColor3f(r, g, b);
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

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

//Render bitmap characters

void RenderString(float x, float y, char* string, void* font, float r = 1, float g = 1, float b = 1)
{
  char *c;

  glColor3f(r, g, b);
  glRasterPos2f(x, y);

  for (c = string;*c != '\0';c++)
  {
      glutBitmapCharacter(font, *c);
  }
}

//Stroke font for Intro

void drawStrokeText(int x, int y, char*string, float w = 1, float r = 1, float g = 1, float b = 1, float sx = 0.3f, float sy = 0.3f)
{
    int z = 0;
    char *c;
    glColor3f(r, g, b);
    glLineWidth(w);
    glPushMatrix();
    glTranslatef(x, y+8,z);
    glScalef(sx, sy , z);

    for (c=string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
    }
    glPopMatrix();
}

//Convert single digit to string

void to_string_digit(char str[], int digit)
{
    str[0] = digit + '0';
    str[1] = '\0';
}

//Convert double digit to string

void to_string_digits(char str[], int digits)
{
    str[0] = digits/10 + '0';
    str[1] = digits%10 + '0';
    str[2] = '\0';
}

//Introduction and our names

void intro(int x, int y)
{
    RenderString(x + 50, y + 350, "Intro ", GLUT_BITMAP_HELVETICA_18);
    drawStrokeText(x - 250, y + 200, "COMPUTER GRAPHICS LAB MINI PROJECT", 2);
    drawStrokeText(x - 100, y, "BLOCKCHAIN SIMULATOR", 3);
    drawStrokeText(x - 100, y - 100, "Press N to create a new simulation instance", 2, 0, 1, 0, 0.15f, 0.15f);
    drawStrokeText(x + 50, y - 400, "A SIMULATOR BY", 2, 1, 1, 1, 0.2f, 0.2f);
    drawStrokeText(x - 300, y - 500, "ARUN R SHENOY 1BY17CS032", 2, 1, 1, 1, 0.2f, 0.2f);
    drawStrokeText(x + 150, y - 500, "CHARAN KALSHETTY 1BY17CS041", 2, 1, 1, 1, 0.2f, 0.2f);
}


//Display block chain

void display_blocks()
{
    RenderString(400, 900, "Viewing Instance of block chain", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(400, 950, "Intro / Blockchain ", GLUT_BITMAP_HELVETICA_18);
    RenderString(400, 850, "Right click to view the Menu", GLUT_BITMAP_9_BY_15);
    int tempx = 0;
    char str[3];

    RenderString(0, y+125, "Block chain (Click on any block to view it's contents)", GLUT_BITMAP_9_BY_15);

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
        if (i == manip_block + 1 || i == manip_block)
        {
            draw_polygon(tempx, y, block_width, block_height, 0.0, 0.0, 0.0);
        }
        else
        {
            draw_polygon(tempx, y, block_width, block_height);
        }
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

    RenderString(0, y - 25, "No of blocks: " , GLUT_BITMAP_8_BY_13, 0, 1, 0);
    RenderString(150, y - 25, str, GLUT_BITMAP_8_BY_13, 0, 1, 0);
    if (manip_block != -2)
    {
        RenderString(0, y - 50, "Blockchain is invalid please press C to contact peer nodes and replace it", GLUT_BITMAP_8_BY_13, 1, 0, 0);
    }
    RenderString(400, 150, "A SIMULATOR BY", GLUT_BITMAP_9_BY_15);
    RenderString(400, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(400, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);
}

//Display open transactions

void display_open_transactions()
{
    int oty = y - 300;
    RenderString(0, oty + 125, "Open Transactions (Click on any transaction to view it's contents)", GLUT_BITMAP_9_BY_15);
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
        RenderString(0, oty + 100 , "No open transactions! Use the menu or press 't' to add a transaction!", GLUT_BITMAP_8_BY_13, 1, 0, 0);
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
    RenderString(0, oty - 25, "No of open transactions: " , GLUT_BITMAP_8_BY_13, 0, 1, 0);
    RenderString(150, oty - 25, str, GLUT_BITMAP_8_BY_13, 0, 1, 0);

}

//Display the transactions in the clicked block

void display_block_transactions()
{
    int oty = 300;
    int tempx = 0;
    char str[3];
    RenderString(0, oty + 125, "Transactions in block (Click on any transaction to view it's contents)", GLUT_BITMAP_9_BY_15);
    if (transactions[clicked_block] >= 9)
    {
        open_transaction_width = 50;
        open_transaction_height = 100;
        open_transaction_font = GLUT_BITMAP_TIMES_ROMAN_10;
    }
    if (transactions[clicked_block] == 0)
    {
        RenderString(0, oty + 100 , "Block has no transactions !", GLUT_BITMAP_8_BY_13, 1, 0, 0);
        return;
    }
    for (int i = 1; i<= transactions[clicked_block]; i++)
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
    if (transactions[clicked_block] <= 9)
    {
        to_string_digit(str, transactions[clicked_block]);
    }
    else
    {
        to_string_digits(str, transactions[clicked_block]);
    }
    RenderString(0, oty - 25, "No of transactions: " , GLUT_BITMAP_8_BY_13, 0, 1, 0);
    RenderString(150, oty - 25, str, GLUT_BITMAP_8_BY_13, 0, 1, 0);
    RenderString(400, 150, "A SIMULATOR BY", GLUT_BITMAP_9_BY_15);
    RenderString(400, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(400, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);
}

//Display the clicked block

void display_block()
{
    int x1 = 350;
    int y1 = 500;
    char block[3];
    char previous_block[3];
    char t[3];


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

    if (manip_block == clicked_block || manip_block + 1 == clicked_block)
    {
        draw_polygon(x1, y1, 300, 300, 0, 0, 0);
    }
    else
    {
        draw_polygon(x1, y1, 300, 300);
    }

    RenderString(400, 900, "Viewing Block", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(500, 900, block, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(400, 950, "Intro / Blockchain / Block", GLUT_BITMAP_HELVETICA_18);
    RenderString(400, 850, "Press B or Esc to go back !", GLUT_BITMAP_8_BY_13);
    RenderString(x1 + 25, y1 + 250, "Index: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 75, y1 + 250, block, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 25, y1 + 225, "Previous Hash: ", GLUT_BITMAP_TIMES_ROMAN_24);
    if (clicked_block == manip_block + 1)
    {
        RenderString(x1 + 125, y1 + 225, "Invalid", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        RenderString(x1 + 125, y1 + 225, previous_block, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    RenderString(x1 + 25, y1 + 200, "Transactions: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 125, y1 + 200, t, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1, y1 - 50, "Press M to manipulate the block", GLUT_BITMAP_8_BY_13);
    RenderString(400, 150, "A SIMULATOR BY", GLUT_BITMAP_9_BY_15);
    RenderString(400, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(400, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);

    display_block_transactions();
}

//Display clicked open transaction

void display_open_transaction()
{
    int x1 = 350;
    int y1 = 500;
    char ot[3];
    draw_polygon(x1, y1, 300, 300);

    if (what_to_do == 7)
    {
        RenderString(400, 950, "Intro / Blockchain / Block / Transaction", GLUT_BITMAP_HELVETICA_18);
    }
    else
    {
        RenderString(400, 950, "Intro / Blockchain / Open Transaction", GLUT_BITMAP_HELVETICA_18);
    }

    if (clicked_ot <= 9)
    {
        to_string_digit(ot, clicked_ot);
    }
    else
    {
        to_string_digits(ot, clicked_ot);
    }
    RenderString(400, 900, "Viewing Transaction", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(540, 900, ot, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(400, 859, "Press B or Esc to go back !", GLUT_BITMAP_8_BY_13);
    RenderString(x1 + 25, y1 + 250, "Transaction:", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 125, y1 + 250, ot, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 25, y1 + 225, "Sender: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 125, y1 + 225, ot, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 25, y1 + 200, "Recipient: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 125, y1 + 200, ot, GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 25, y1 + 175, "Amount: ", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(x1 + 125, y1 + 175, "10.0", GLUT_BITMAP_TIMES_ROMAN_24);
    RenderString(400, 150, "A SIMULATOR BY", GLUT_BITMAP_9_BY_15);
    RenderString(400, 100, "ARUN R SHENOY 1BY17CS032", GLUT_BITMAP_9_BY_15);
    RenderString(400, 50, "CHARAN KALSHETTY 1BY17CS041", GLUT_BITMAP_9_BY_15);
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


//Display function called again and again by glut

void display()
{
    glutFullScreen();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //Display Introduction

    if (what_to_do == -1)
    {
        intro(350, 600);
    }

    //Display first simulation instance

    if (what_to_do == 0)
    {
        display_blocks();
        display_open_transactions();
    }

    //Mine a block

    if (what_to_do == 1)
    {
        if (manip_block != -2)
        {
            what_to_do = 0;
            return;
        }
        add_block();
        what_to_do = 0;
    }

    //Add open transaction

    if (what_to_do == 2)
    {
        x = x + open_transaction_width + padding;
        no_of_ot += 1;
        what_to_do = 0;

    }

    //Reset Simulation

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
        transactions[manip_block] = temp_transac;
        manip_block = -2;
        temp_transac = 0;
        what_to_do = 0;
    }

    //Exit Simulation

    if (what_to_do == 4)
    {
        int win = glutGetWindow();
        glutDestroyWindow(win);
        return;
    }

    //Display Block

    if (what_to_do == 5)
    {
        if (clicked_block > no_of_blocks)
        {
            what_to_do = 0;
        }
        else
        {
            display_block();
        }
    }

    //Display Open Transaction

    if (what_to_do == 6)
    {
        if (clicked_ot > no_of_ot)
        {
            what_to_do = 0;
        }
        else
        {
            display_open_transaction();
        }
    }

    //Display Block Transaction

    if (what_to_do == 7)
    {
        if (clicked_ot > transactions[clicked_block])
        {
            what_to_do = 5;
        }
        else
        {
            display_open_transaction();
        }
    }

    //Manipulate a block

    if (what_to_do == 8)
    {
        if (manip_block == clicked_block || manip_block + 1 == clicked_block)
        {
            what_to_do = 5;
            return;
        }
        manip_block = clicked_block;
        temp_transac = transactions[manip_block];
        transactions[manip_block] = 4;
        what_to_do = 5;
    }

    //Fix manipulated block

    if (what_to_do == 9)
    {
        transactions[manip_block] = temp_transac;
        manip_block = -2;
        temp_transac = 0;
        what_to_do = 0;
    }

    //Display to screen

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
    if (key == 'n' && what_to_do == -1)
    {
        what_to_do = 0;
    }
    if (key == 'm')
    {
        if (what_to_do == 5)
        {
            what_to_do = 8;
        }
        else
        {
            what_to_do = 1;
        }
    }
    if (key == 't' && what_to_do == 0)
    {
        what_to_do = 2;
    }
    if (key == 'r' && what_to_do == 0)
    {
        what_to_do = 3;
    }
    if ((int)key == 27)
    {
        if (what_to_do == 0)
        {
            what_to_do = -1;
        }
        else if (what_to_do == 5 || what_to_do == 6)
        {
            what_to_do = 0;
        }
        else if (what_to_do == 7)
        {
            what_to_do = 5;
        }
        else
        {
            what_to_do = 4;
        }
    }
    if (key == 'b')
    {
        if (what_to_do == 7)
        {
            what_to_do = 5;
        }
        else
        {
            what_to_do = 0;
        }
    }
    if (key == 'c' && what_to_do == 0)
    {
        what_to_do = 9;
    }
    display();
}

//Mouse Listener
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && y >= 1000 - (::y + block_height) && y <= 1000 - ::y && what_to_do == 0)
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
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && y >= 1000 - (::y - 200 + open_transaction_height) && y <= 1000 - (::y - 200) && what_to_do == 0)
    {
        if (no_of_ot < 9)
        {
            clicked_ot = ((x) / (184)) + 1;
            what_to_do = 6;
        }
        else
        {
            clicked_ot = ((x) / 105) + 1;
            what_to_do = 6;
        }
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP && y >= 1000 - (::y - 200 + open_transaction_height) && y <= 1000 - (::y - 200) && what_to_do == 5)
    {
        if (transactions[clicked_block] < 9)
        {
            clicked_ot = ((x) / (184)) + 1;
            what_to_do = 7;
        }
        else
        {
            clicked_ot = ((x) / 105) + 1;
            what_to_do = 7;
        }
    }
}


//Initialize graphics system

void init()
{
    glClearColor(0, 0.6, 0.6, 1);
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
