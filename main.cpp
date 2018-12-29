//-----------------------------------------------------------------------------
//                                                              2008/6/26
//                          A First Sample Code
//                                                              by????
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>

void WindowSize(int , int );            //????????????
void Keyboard(unsigned char , int, int );   //??????
void Display(void);                     //??

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(400,400);         //????
   glutInitWindowPosition(600,80);         //????????
   glutCreateWindow("???????");      //????
   
   //?????????Callback??
   glutReshapeFunc(WindowSize);
   glutKeyboardFunc(Keyboard);
   glutDisplayFunc(Display);
   glutMainLoop();
   return 0;
}

void Display(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,0,10.0f,0,0,0,0,1,0);   //????????
   glBegin(GL_TRIANGLES);
      glColor3f( 1, 0, 0);glVertex3f( 8.6603, -5, 0);
      glColor3f( 0, 1, 0);glVertex3f(      0, 10, 0);
      glColor3f( 0, 0, 1);glVertex3f(-8.6603, -5, 0);
   glEnd();
   glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
   printf("????????%x\t???????????(%d,%d)\n", key, x, y);
}

void WindowSize(int w, int h)
{
   printf("???????%dX%d\n",w,h);
   glViewport(0, 0, w, h);            //????????,??????
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-10,10,-10,10,-10,10);      //????
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
} 
