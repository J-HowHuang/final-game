#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include "game.h"
using namespace std;

void WindowSize(int , int );            //????????????
void Keyboard(unsigned char , int, int );   //??????
void Display(void);                     //??
void Timer(int);

Character _1p(CHAR_WIDTH, CHAR_HEIGHT, 1);
Character _2p(MAP_WIDTH - CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2);
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
   glutTimerFunc(100, Timer, 0);
   glutMainLoop();
   return 0;
}

void Display(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,0,20.0f,0,0,0,0,1,0);   //should be modified
   _1p.drawCharacter();
   _2p.drawCharacter();
   glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	cout << key;
	switch(key){
		case('w'):
			if(_1p.getDirection() != UP){
				_1p.setDirection(UP);
			}
			_1p.moveStep();
			
			break;
		case('a'):
			if(_1p.getDirection() != LEFT){
				_1p.setDirection(LEFT);
			}
			_1p.moveStep();
			break;
		case('s'):
			if(_1p.getDirection() != DOWN){
				_1p.setDirection(DOWN);
			}
			_1p.moveStep();
			break;
		case('d'):
			if(_1p.getDirection() != RIGHT){
				_1p.setDirection(RIGHT);
			}
			_1p.moveStep();
			break;
	}
}
void Timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timer, 0);
}
void WindowSize(int w, int h)
{
   glViewport(0, 0, w, h);            //????????,??????
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0,MAP_WIDTH, 0,MAP_HEIGHT,-200,10);      //????
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
} 
