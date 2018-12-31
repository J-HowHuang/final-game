#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include "game.h"
using namespace std;

void WindowSize(int , int );            //????????????
void Keyboard(unsigned char , int, int );   //??????
void KeyboardUp(unsigned char, int, int);
void Display(void);                     //??
void Timer(int);

Character _1p(CHAR_WIDTH, CHAR_HEIGHT, 1);
Character _2p(MAP_WIDTH - CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2);
bool keyStates[256] = {0};
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
   glutIgnoreKeyRepeat(1);
   glutKeyboardFunc(Keyboard);
   glutKeyboardUpFunc(KeyboardUp);
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
   gluLookAt(0,0,10.0f,0,0,0,0,1,0);   //should be modified
   _1p.drawCharacter();
   _2p.drawCharacter();
   glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key){
		//1p character moving
		case('w'):
			if(_1p.getDirection() != UP){
				_1p.setDirection(UP);
			}
			keyStates['w'] = true;
			break;
		case('a'):
			if(_1p.getDirection() != LEFT){
				_1p.setDirection(LEFT);
			}
			keyStates['a'] = true;
			break;
		case('s'):
			if(_1p.getDirection() != DOWN){
				_1p.setDirection(DOWN);
			}
			keyStates['s'] = true;
			break;
		case('d'):
			if(_1p.getDirection() != RIGHT){
				_1p.setDirection(RIGHT);
			}
			keyStates['d'] = true;
			break;
		//2p character moving
		case('i'):
			if(_2p.getDirection() != UP){
				_2p.setDirection(UP);
			}
			keyStates['i'] = true;
			
			break;
		case('j'):
			if(_2p.getDirection() != LEFT){
				_2p.setDirection(LEFT);
			}
			keyStates['j'] = true;
			break;
		case('k'):
			if(_2p.getDirection() != DOWN){
				_2p.setDirection(DOWN);
			}
			keyStates['k'] = true;
			break;
		case('l'):
			if(_2p.getDirection() != RIGHT){
				_2p.setDirection(RIGHT);
			}
			keyStates['l'] = true;
			break;
	}
}
void KeyboardUp(unsigned char key, int x, int y){
	switch(key){
		//1p character moving
		case('w'):
			_1p.setDirection(UP);
			keyStates['w'] = false;
			break;
		case('a'):
			_1p.setDirection(LEFT);
			keyStates['a'] = false;
			break;
		case('s'):
			_1p.setDirection(DOWN);
			keyStates['s'] = false;
			break;
		case('d'):
			_1p.setDirection(RIGHT);
			keyStates['d'] = false;
			break;
		//2p character moving
		case('i'):
			_2p.setDirection(UP);
			keyStates['i'] = false;
			break;
		case('j'):
			_2p.setDirection(LEFT);
			keyStates['j'] = false;
			break;
		case('k'):
			_2p.setDirection(DOWN);
			keyStates['k'] = false;
			break;
		case('l'):
			_2p.setDirection(RIGHT);
			keyStates['l'] = false;
			break;
	}
}
void Timer(int){
	if(keyStates['w'] == true)
		_1p.move(UP);
	if(keyStates['a'] == true)
		_1p.move(LEFT);
	if(keyStates['s'] == true)
		_1p.move(DOWN);
	if(keyStates['d'] == true)
		_1p.move(RIGHT);
	if(keyStates['i'] == true)
		_2p.move(UP);
	if(keyStates['j'] == true)
		_2p.move(LEFT);
	if(keyStates['k'] == true)
		_2p.move(DOWN);
	if(keyStates['l'] == true)
		_2p.move(RIGHT);
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
