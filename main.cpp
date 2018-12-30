#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include "game.h"
using namespace std;

void WindowSize(int , int );            //????????????
void Keyboard(unsigned char , int, int );   //??????
void Display(void);                     //??


Character _1p(0, 0);
const char GAME_NAME[] = {"awesome game"};
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(1080,720);         //????
   glutInitWindowPosition(600,80);         //????????
   glutCreateWindow(GAME_NAME);      //????
   
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
   gluLookAt(540,360,500,540,360,0,0,1,0);   //should be modified
   _1p.drawCharacter();
   glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	
}

void WindowSize(int w, int h)
{
   glViewport(0, 0, w, h);            
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 1080, 0, 720, -10, 10);      //should be modified
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
} 
