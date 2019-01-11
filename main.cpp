
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<windows.h>
#include <GL\freeglut.h> 
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include <cmath>
#include "game.h"
#include "button.h"
using namespace std;

void WindowSize(int , int );            //????????????
void loadTexture(char* filenamem, GLuint id);
void Keyboard(unsigned char , int, int );   //??????
void KeyboardUp(unsigned char, int, int);
void Mouse(int, int, int, int);
void Display(void);                     //??
void Timer(int);
void ShootTimer(int);
//
Character _1p(CHAR_WIDTH, CHAR_HEIGHT, 1);
Character _2p(MAP_WIDTH - CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2);
Mirror _1pMirror(MAP_WIDTH - CHAR_WIDTH, CHAR_HEIGHT, 1, 60);
Mirror _2pMirror(CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2, 60);
Mirror margin1(MAP_WIDTH / 2, 3, 0, MAP_WIDTH, UP);
Mirror margin2(MAP_WIDTH / 2, MAP_HEIGHT - 3, 0, MAP_WIDTH, DOWN);
Mirror margin3(3, MAP_HEIGHT / 2, 0, MAP_HEIGHT, LEFT);
Mirror margin4(MAP_WIDTH - 3, MAP_HEIGHT / 2, 0, MAP_HEIGHT, RIGHT);
Button start("start", MAP_WIDTH / 2 - 81, MAP_HEIGHT / 2 - 32, 172, 64);
Button tutorial("tutorial", MAP_WIDTH / 2 - 81, MAP_HEIGHT / 2 - 116, 172, 64);
Button quit("quit", MAP_WIDTH / 2 - 81, MAP_HEIGHT / 2 - 200, 172, 64);
double music = 0.5;
double sound = 0.5;
Obstacle **tree = new Obstacle *[5];
int tree_count = 2;
bool keyStates[256] = {0};
const char GAME_NAME[] = {"awesome game"};
int mode = GAME_MENU;
bool gamePause = false;
bool startPressed = false;
bool tutorialPressed = false;
bool quitPressed = false;
bool mode1Pressed = false;
bool mode2Pressed = false;
int main(int argc, char** argv)
{
    tree[1] = new Obstacle(500,360,500 + OBSTACLE_WIDTH,360 + OBSTACLE_WIDTH);
    tree[2] = new Obstacle(200,100,200 + OBSTACLE_WIDTH,100 + OBSTACLE_WIDTH);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080,720);         //????
    glutInitWindowPosition(600,80);         //????????
    glutCreateWindow(GAME_NAME);      //????
	glEnable(GL_BLEND); 
	glDisable(GL_DEPTH_TEST);
    //?????????Callback??
    glutReshapeFunc(WindowSize);
    glutIgnoreKeyRepeat(1);
    glutMouseFunc(Mouse);
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(mode == GAME_MENU){
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
	/*	GLuint start_button;
		loadTexture("start.bmp", start_button);
		glBindTexture(GL_TEXTURE_2D, start_button);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT);
			glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP);
			glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP);
			glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT);
		glEnd();
		if(startPressed){
			GLuint start_button_pressed;
			loadTexture("start_pressed.bmp", start_button_pressed);
			glBindTexture(GL_TEXTURE_2D, start_button_pressed);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT);
				glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP);
				glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP);
				glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT);
			glEnd();
		}*/
		start.drawButton() ;
		tutorial.drawButton() ;
		quit.drawButton() ;
		glutSwapBuffers();
	}
	if(mode == GAME_MODE_1){
		
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0);   //should be modified
		_1p.drawCharacter();
		_2p.drawCharacter();
		_1pMirror.drawMirror();
		_2pMirror.drawMirror();
    	tree[1]->drawObstacle();
    	tree[2]->drawObstacle();
		margin1.drawMirror();
		margin2.drawMirror();
		margin3.drawMirror();
		margin4.drawMirror();
		for(int i = 0 ; i < _1p.getBulletCount() ; i++)
		{
			if(_1p.pBullet[i]->live)
		    	_1p.pBullet[i]->drawBullet();
		}
		for(int i = 0 ; i < _2p.getBulletCount() ; i++)
		{
			if(_2p.pBullet[i]->live)
		   		 _2p.pBullet[i]->drawBullet();
		}
		if(gamePause){
			glColor4f(0, 0, 0, 0.5);
			glRectd(0, 0, MAP_WIDTH, MAP_HEIGHT);
			glColor3f(0.75, 0.75, 0.75);
			glLoadIdentity();
			GLuint setting_text_1;
			loadTexture("pause.bmp", setting_text_1);
			glBindTexture(GL_TEXTURE_2D, setting_text_1);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 1); glVertex2f(MAP_WIDTH / 2 - 256 , MAP_HEIGHT / 2 + 128);
				glTexCoord2f(0, 0); glVertex2f(MAP_WIDTH / 2 - 256 , MAP_HEIGHT / 2 + 128 - 256);
				glTexCoord2f(1, 0); glVertex2f(MAP_WIDTH / 2 - 256 + 512, MAP_HEIGHT / 2 + 128 - 256);
				glTexCoord2f(1, 1); glVertex2f(MAP_WIDTH / 2 - 256 + 512, MAP_HEIGHT / 2 + 128);
			glEnd();
		}
		glutSwapBuffers();
	}
	if(mode == GAME_MODE_SELECT){
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		GLuint mode1_button;
		loadTexture("mod1.bmp", mode1_button);
		glBindTexture(GL_TEXTURE_2D, mode1_button);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT + 96);
			glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP + 96);
			glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP + 96);
			glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT + 96);
		glEnd();
	/*	if(mode1Pressed){
			GLuint mode1_button_pressed;
			loadTexture("mod1_pressed.bmp", mode1_button_pressed);
			glBindTexture(GL_TEXTURE_2D, mode1_button_pressed);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT + 96);
				glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP + 96);
				glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP + 96);
				glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT + 96);
			glEnd();
		}*/
		
		GLuint mode2_button;
		loadTexture("mod2.bmp", mode2_button);
		glBindTexture(GL_TEXTURE_2D, mode2_button);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT - 96);
			glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP - 96);
			glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP - 96);
			glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT - 96);
		glEnd();
	/*	if(mode2Pressed){
			GLuint mode2_button_pressed;
			loadTexture("mod2_pressed.bmp", mode2_button_pressed);
			glBindTexture(GL_TEXTURE_2D, mode2_button_pressed);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT - 96);
				glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP - 96);
				glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP - 96);
				glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT - 96);
			glEnd();
		}*/
		glutSwapBuffers();
	}
}
void Mouse(int button, int state, int x, int y){
	if(mode == GAME_MENU){
		if(x > START_BUTTON_LEFT && x < START_BUTTON_RIGHT && y > START_BUTTON_BOT && y < START_BUTTON_UP){
			if(state == 0){
				startPressed = true;
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay(); 
			}
			if(state){
				mode = GAME_MODE_SELECT;
				glutPostRedisplay();
				cout << "game start\n";
			}
		}
		if(x > TUTORIAL_BUTTON_LEFT && x < TUTORIAL_BUTTON_RIGHT && y > TUTORIAL_BUTTON_BOT && y < TUTORIAL_BUTTON_UP){
			if(state == 0){
				tutorialPressed = true;
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
			}
			if(state){
				//mode = GAME_TUTORIAL ;
				glutPostRedisplay() ;
			}
		}
		if(x > QUIT_BUTTON_LEFT && x < QUIT_BUTTON_RIGHT && y > QUIT_BUTTON_BOT && y < QUIT_BUTTON_UP){
			if(state == 0){
				quitPressed = true;
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
			}
			if(state){
				glutDestroyWindow(1); 
			}
		}
	}
	if(mode == GAME_MODE_SELECT){
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		GLuint mode1_button;
		loadTexture("mod1.bmp", mode1_button);
		glBindTexture(GL_TEXTURE_2D, mode1_button);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT + 96);
			glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP + 96);
			glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP + 96);
			glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT + 96);
		glEnd();
		if(mode1Pressed){
			GLuint mode1_button_pressed;
			loadTexture("mod1_pressed.bmp", mode1_button_pressed);
			glBindTexture(GL_TEXTURE_2D, mode1_button_pressed);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT + 96);
				glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP + 96);
				glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP + 96);
				glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT + 96);
			glEnd();
		}
		
		GLuint mode2_button;
		loadTexture("mod1.bmp", mode2_button);
		glBindTexture(GL_TEXTURE_2D, mode2_button);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT - 96);
			glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP - 96);
			glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP - 96);
			glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT - 96);
		glEnd();
		if(mode2Pressed){
			GLuint mode1_button_pressed;
			loadTexture("mod1_pressed.bmp", mode1_button_pressed);
			glBindTexture(GL_TEXTURE_2D, mode1_button_pressed);
			glBegin(GL_POLYGON);
			
				glTexCoord2f(0, 0); glVertex2f(START_BUTTON_LEFT, START_BUTTON_BOT - 96);
				glTexCoord2f(0, 1); glVertex2f(START_BUTTON_LEFT, START_BUTTON_UP - 96);
				glTexCoord2f(1, 1); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_UP - 96);
				glTexCoord2f(1, 0); glVertex2f(START_BUTTON_RIGHT, START_BUTTON_BOT - 96);
			glEnd();
		}
		glutSwapBuffers();
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	if(mode == GAME_MODE_1){
		switch(key){
        case('w'):
            _1p.shoot(_1p.getBulletCount());
            glutPostRedisplay();
            keyStates['w'] = true;
            break;
        case('7'):
            _2p.shoot(_2p.getBulletCount());
            glutPostRedisplay();
            keyStates['7'] = true;
            break;
        case(27):
        	gamePause = !gamePause;
        	glutPostRedisplay();
        	break;
        default:
        	keyStates[key] = true;
        	break;
		}
	}
}
void KeyboardUp(unsigned char key, int x, int y){
	if(mode == GAME_MODE_1){
		switch(key){
	        case('2'):
	            _1p.moveTowardMirror(_1pMirror);
	            glutPostRedisplay();
	            keyStates['2'] = false;
	            break;
	        case('1'):
	            _2p.moveTowardMirror(_2pMirror);
	            glutPostRedisplay();
	            keyStates['1'] = false;
	            break;
	            
	        default:
	            keyStates[key] = false;
	            break;
		}
	}
    
}
void ShootTimer(int)
{
    if(keyStates['w'] == true)
        _1p.shoot(_1p.getBulletCount());
    
    if(keyStates['7'] == true)
        _2p.shoot(_2p.getBulletCount());
    glutPostRedisplay();
    glutTimerFunc(1000 / DEFAULT_SHOOTING_SPEED, ShootTimer, 0);
}
void Timer(int)
{
    if(mode == GAME_MODE_1){
    	if(keyStates['g'] == true)
	    {
	        _1pMirror.move(UP);
	        if(_1pMirror.disToObstacle(*tree[1]))
	            _1pMirror.move(DOWN);
	        else if(_1pMirror.disToObstacle(*tree[2]))
	            _1pMirror.move(DOWN);
	    }
	    
	    if(keyStates['v'] == true)
	    {
	        _1pMirror.move(LEFT);
	        if(_1pMirror.disToObstacle(*tree[1]))
	            _1pMirror.move(RIGHT);
	        else if(_1pMirror.disToObstacle(*tree[2]))
	            _1pMirror.move(RIGHT);
	    }
	    if(keyStates['b'] == true)
	    {
	        _1pMirror.move(DOWN);
	        if(_1pMirror.disToObstacle(*tree[1]))
	            _1pMirror.move(UP);
	        else if(_1pMirror.disToObstacle(*tree[2]))
	            _1pMirror.move(UP);
	    }
	    if(keyStates['n'] == true)
	    {
	        _1pMirror.move(RIGHT);
	        if(_1pMirror.disToObstacle(*tree[1]))
	            _1pMirror.move(LEFT);
	        else if(_1pMirror.disToObstacle(*tree[2]))
	            _1pMirror.move(LEFT);
	    }
	    if(keyStates['l'] == true)
	    {
	        _2pMirror.move(UP);
	        if(_2pMirror.disToObstacle(*tree[1]))
	            _2pMirror.move(DOWN);
	        else if(_2pMirror.disToObstacle(*tree[2]))
	            _2pMirror.move(DOWN);
	    }
	    
	    if(keyStates[','] == true)
	    {
	        _2pMirror.move(LEFT);
	        if(_2pMirror.disToObstacle(*tree[1]))
	            _2pMirror.move(RIGHT);
	        else if(_2pMirror.disToObstacle(*tree[2]))
	            _2pMirror.move(RIGHT);
	    }
	    if(keyStates['.'] == true)
	    {
	        _2pMirror.move(DOWN);
	        if(_2pMirror.disToObstacle(*tree[1]))
	            _2pMirror.move(UP);
	        else if(_2pMirror.disToObstacle(*tree[2]))
	            _2pMirror.move(UP);
	    }
	    if(keyStates['/'] == true)
	    {
	        _2pMirror.move(RIGHT);
	        if(_2pMirror.disToObstacle(*tree[1]))
	            _2pMirror.move(LEFT);
	        else if(_2pMirror.disToObstacle(*tree[2]))
	            _2pMirror.move(LEFT);
	    }
	    if(keyStates['f'] == true)
	        _1pMirror.rotate(1);
	    if(keyStates['h'] == true)
	        _1pMirror.rotate(-1);
	    if(keyStates['k'] == true)
	        _2pMirror.rotate(1);
	    if(keyStates[';'] == true)
	        _2pMirror.rotate(-1);
	    if(keyStates['q'] == true)
	        _1p.rotate(1);
	    if(keyStates['e'] == true)
	        _1p.rotate(-1);
	    if(keyStates['6'] == true)
	        _2p.rotate(1);
	    if(keyStates['8'] == true)
	        _2p.rotate(-1);
	    if(_1p.get_x() > MAP_WIDTH)
	        _1p.set_x(MAP_WIDTH);
	    if(_1p.get_x() < 0)
	        _1p.set_x(0);
	    if(_1p.get_y() > MAP_HEIGHT)
	        _1p.set_y(MAP_HEIGHT);
	    if(_1p.get_y() < 0)
	        _1p.set_y(0);
	    if(_2p.get_x() > MAP_WIDTH)
	        _2p.set_x(MAP_WIDTH);
	    if(_2p.get_x() < 0)
	        _2p.set_x(0);
	    if(_2p.get_y() > MAP_HEIGHT)
	        _2p.set_y(MAP_HEIGHT);
	    if(_2p.get_y() < 0)
	        _2p.set_y(0);
	    
	    if(_1pMirror.get_x() > MAP_WIDTH)
	        _1pMirror.set_x(MAP_WIDTH);
	    if(_1pMirror.get_x() < 0)
	        _1pMirror.set_x(0);
	    if(_1pMirror.get_y() > MAP_HEIGHT)
	        _1pMirror.set_y(MAP_HEIGHT);
	    if(_1pMirror.get_y() < 0)
	        _1pMirror.set_y(0);
	    if(_2pMirror.get_x() > MAP_WIDTH)
	        _2pMirror.set_x(MAP_WIDTH);
	    if(_2pMirror.get_x() < 0)
	        _2pMirror.set_x(0);
	    if(_2pMirror.get_y() > MAP_HEIGHT)
	        _2pMirror.set_y(MAP_HEIGHT);
	    if(_2pMirror.get_y() < 0)
	        _2pMirror.set_y(0);
	    //
	    if(_1p.times != 0)
	    {
	        _1p.move();
	        _1p.count++;
	        if(_1p.count == _1p.times)
	        {
	            _1p.count = 0;
	            _1p.times = 0;
	            _1p.setSpeed(0);
	        }
	    }
	    if(_2p.times != 0)
	    {
	        _2p.move();
	        _2p.count++;
	        if(_2p.count == _2p.times)
	        {
	            _2p.count = 0;
	            _2p.times = 0;
	            _2p.setSpeed(0);
	        }
	    }
	    //
	    /*
	     if(_1p.disToObstacle(tree1))
	     {
	     if(_1p.get_x() > tree1.coodLD_x - 1 && (_1p.get_y() <= tree1.coodRT_y + 1 && _1p.get_y() >= tree1.coodLD_y - 1))
	     _1p.set_x(tree1.coodLD_x - 1);
	     if(_1p.get_y() > tree1.coodLD_y - 1 && (_1p.get_x() <= tree1.coodRT_x + 1 && _1p.get_x() >= tree1.coodLD_x - 1))
	     _1p.set_y(tree1.coodLD_y - 1);
	     if(_1p.get_x() < tree1.coodRT_x + 1 && (_1p.get_y() >= tree1.coodLD_y - 1 && _1p.get_y() <= tree1.coodRT_y + 1))
	     _1p.set_x(tree1.coodRT_x + 1);
	     if(_1p.get_y() < tree1.coodRT_y + 1 && (_1p.get_x() >= tree1.coodLD_x - 1 && _1p.get_x() <= tree1.coodRT_x + 1))
	     _1p.set_y(tree1.coodRT_y + 1);
	     }
	     */
	    //
	    for(int i = 0 ; i < _1p.getBulletCount(); i++)
	    {
	        _1p.pBullet[i]->move();
	        _1p.pBullet[i]->reflect(_1pMirror);
	        _1p.pBullet[i]->reflect(_2pMirror);
	        _1p.pBullet[i]->reflect(margin1);
	        _1p.pBullet[i]->reflect(margin2);
	        _1p.pBullet[i]->reflect(margin3);
	        _1p.pBullet[i]->reflect(margin4);
	        _1p.pBullet[i]->getInObstacle(*tree[1]);
	        _1p.pBullet[i]->getInObstacle(*tree[2]);
	        if(abs(_1p.pBullet[i]->get_x() - _2p.get_x()) < CHAR_WIDTH / 2 && abs(_1p.pBullet[i]->get_y() - _2p.get_y()) < CHAR_HEIGHT / 2){
	            if(_1p.pBullet[i]->live){
	                _2p.healthP -= _1p.pBullet[i]->get_atk();
	                cout << "1P: " << _1p.healthP << " 2P: " << _2p.healthP << endl;
	                _1p.pBullet[i]->live = false;
	            }
	        }
	    }
	    for(int i = 0 ; i < _2p.getBulletCount(); i++)
	    {
	        _2p.pBullet[i]->move();
	        _2p.pBullet[i]->reflect(_1pMirror);
	        _2p.pBullet[i]->reflect(_2pMirror);
	        _2p.pBullet[i]->reflect(margin1);
	        _2p.pBullet[i]->reflect(margin2);
	        _2p.pBullet[i]->reflect(margin3);
	        _2p.pBullet[i]->reflect(margin4);
	        _2p.pBullet[i]->getInObstacle(*tree[1]);
	        _2p.pBullet[i]->getInObstacle(*tree[2]);
	        if(abs(_2p.pBullet[i]->get_x() - _1p.get_x()) < CHAR_WIDTH / 2 && abs(_2p.pBullet[i]->get_y() - _1p.get_y()) < CHAR_HEIGHT / 2){
	            if(_2p.pBullet[i]->live){
	                _1p.healthP -= _2p.pBullet[i]->get_atk();
	                cout << "1P: " << _1p.healthP << " 2P: " << _2p.healthP << endl;
	                _2p.pBullet[i]->live = false;
	            }
	        }
	    }
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
