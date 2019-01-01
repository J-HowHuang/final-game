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
void ShootTimer(int);
//
const int MAX_BulletOnPlane = 250;
Bullet ***pBullet = new Bullet **[3];
pBullet[1] = new Bullet *[MAX_BulletOnPlane]; //這行怪怪的
pBullet[2] = new Bullet *[MAX_BulletOnPlane]; //這行也怪怪的
int _1pBulletCount = 0;
int _2pBulletCount = 0;
//
Character _1p(CHAR_WIDTH, CHAR_HEIGHT, 1);
Character _2p(MAP_WIDTH - CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2);
Mirror _1pMirror(MAP_WIDTH - CHAR_WIDTH, CHAR_HEIGHT, 1);
Mirror _2pMirror(CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2);
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
   glutTimerFunc(100, ShootTimer, 0);
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
   _1pMirror.drawMirror();
   _2pMirror.drawMirror();
    for(int i = 0 ; i < _1pBulletCount ; i++)
    {
        pBullet[1][i]->drawBullet();
    }
    for(int i = 0 ; i < _2pBulletCount ; i++)
    {
        pBullet[2][i]->drawBullet();
    }
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
		case('7'):
			if(_2p.getDirection() != UP){
				_2p.setDirection(UP);
			}
			keyStates['7'] = true;
			break;
		case('y'):
			if(_2p.getDirection() != LEFT){
				_2p.setDirection(LEFT);
			}
			keyStates['y'] = true;
			break;
		case('u'):
			if(_2p.getDirection() != DOWN){
				_2p.setDirection(DOWN);
			}
			keyStates['u'] = true;
			break;
		case('i'):
			if(_2p.getDirection() != RIGHT){
				_2p.setDirection(RIGHT);
			}
			keyStates['i'] = true;
			break;
		//1p mirror moving
		case('g'):
			keyStates['g'] = true;
			break;
		case('v'):
			keyStates['v'] = true;
			break;
		case('b'):
			keyStates['b'] = true;
			break;
		case('n'):
			keyStates['n'] = true;
			break;
		//2p mirror moving
		case('l'):
			keyStates['l'] = true;
			break;
		case(','):
			keyStates[','] = true;
			break;
		case('.'):
			keyStates['.'] = true;
			break;
		case('/'):
			keyStates['/'] = true;
			break;
		//1p mirror rotate
		case('f'):
			keyStates['f'] = true;
			_1pMirror.rotate(1);
			break;
		case('h'):
			keyStates['h'] = true;
			_1pMirror.rotate(-1);			
			break;
		//2p mirror rotate
		case('k'):
			keyStates['k'] = true;
			_2pMirror.rotate(1);
			break;
		case(';'):
			keyStates[';'] = true;
			_2pMirror.rotate(-1);
			break;
            // shoot
        case('1'):
            keyStates['1'] = true;
            break;
        case('2'):
            keyStates['2'] = true;
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
		case('7'):
			_2p.setDirection(UP);
			keyStates['7'] = false;
			break;
		case('y'):
			_2p.setDirection(LEFT);
			keyStates['y'] = false;
			break;
		case('u'):
			_2p.setDirection(DOWN);
			keyStates['u'] = false;
			break;
		case('i'):
			_2p.setDirection(RIGHT);
			keyStates['i'] = false;
			break;
		//1p mirror moving
		case('g'):
			keyStates['g'] = false;
			break;
		case('v'):
			keyStates['v'] = false;
			break;
		case('b'):
			keyStates['b'] = false;
			break;
		case('n'):
			keyStates['n'] = false;
			break;
		//2p mirror moving
		case('l'):
			keyStates['l'] = false;
			break;
		case(','):
			keyStates[','] = false;
			break;
		case('.'):
			keyStates['.'] = false;
			break;
		case('/'):
			keyStates['/'] = false;
			break;
        // shoot
        case('1'):
            keyStates['1'] = false;
            break;
        case('2'):
            keyStates['2'] = false;
            break;
	}
}
void ShootTimer(int)
{
    if(keyStates['1'] == true)
        _1p.shoot(_1pBulletCount);
    
    if(keyStates['1'] == true)
        _2p.shoot(_2pBulletCount);
    glutPostRedisplay();
    glutTimerFunc(1000 / (FPS * 10), ShootTimer, 0);
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
	if(keyStates['7'] == true)
		_2p.move(UP);
	if(keyStates['y'] == true)
		_2p.move(LEFT);
	if(keyStates['u'] == true)
		_2p.move(DOWN);
	if(keyStates['i'] == true)
		_2p.move(RIGHT);
	if(keyStates['g'] == true)
		_1pMirror.move(UP);
	if(keyStates['v'] == true)
		_1pMirror.move(LEFT);
	if(keyStates['b'] == true)
		_1pMirror.move(DOWN);
	if(keyStates['n'] == true)
		_1pMirror.move(RIGHT);
	if(keyStates['l'] == true)
		_2pMirror.move(UP);
	if(keyStates[','] == true)
		_2pMirror.move(LEFT);
	if(keyStates['.'] == true)
		_2pMirror.move(DOWN);
	if(keyStates['/'] == true)
		_2pMirror.move(RIGHT);
    for(int i = 0 ; i < _1pBulletCount ; i++)
    {
        pBullet[1][i]->move();
    }
    for(int i = 0 ; i < _2pBulletCount ; i++)
    {
        pBullet[2][i]->move();
    }
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
