#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <GL\freeglut.h> 
#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include <cmath>
#include <ctime>
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
Button start("start", MAP_WIDTH / 2 - 86 , MAP_HEIGHT / 2 - 32, 172, 64);
Button tutorial("tutorial", MAP_WIDTH / 2 - 86, MAP_HEIGHT / 2 - 116, 172, 64) ;
Button quit("quit", MAP_WIDTH / 2 - 86 , MAP_HEIGHT / 2 - 200, 172 , 64);
Button back("menu", MAP_WIDTH / 2 + 300, MAP_HEIGHT / 2 - 300, 172, 64);
Button tutorialBg("tutorialBackground", 0, 0, 1000, 720);
Button close("close_1", 0, 0, 1000, 720);
Button backGround("shit", 0, 0, 1080, 720);
Button yes("yes" , MAP_WIDTH / 2 - 278 , MAP_HEIGHT / 2 - 116 , 172 , 64) ;
Button no("no" , MAP_WIDTH / 2 + 86 , MAP_HEIGHT / 2 - 116 , 172 , 64) ;
Button mod1("mod1", MAP_WIDTH / 2 - 172 , MAP_HEIGHT / 2 + 96, 344, 128);
Button mod2("mod2", MAP_WIDTH / 2 - 172 , MAP_HEIGHT / 2 - 96, 344, 128);
Button blueWin("bluewin", 0, 0, MAP_WIDTH, MAP_HEIGHT);
Button redWin("redwin", 0, 0, MAP_WIDTH, MAP_HEIGHT);
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
bool closePressed = false ;
bool yesPressed = false ;
bool noPressed = false ;
bool backPressed = false ;
//for game mode 2
bool  BulletGeneratorStart = false;
Bullet **BulletForHockey;
int main(int argc, char** argv)
{
    tree[1] = new Obstacle(500,360,500 + OBSTACLE_WIDTH,360 + OBSTACLE_WIDTH);
    tree[2] = new Obstacle(200,100,200 + OBSTACLE_WIDTH,100 + OBSTACLE_WIDTH);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080,720);         //????
    glutInitWindowPosition(100,0);         //????????
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
    glutTimerFunc(0, Timer, 0);
    glutTimerFunc(0, ShootTimer, 0);
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
		//backGround.drawButton() ;
		start.drawButton() ;
		tutorial.drawButton() ;
		quit.drawButton() ;
		glutSwapBuffers();
	}
	if(mode == GAME_TUTORIAL){
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		tutorialBg.drawButton() ;
		back.drawButton() ;
		glutSwapBuffers();
		glEnd();
	}
	if(mode == GAME_CLOSE)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		close.drawButton() ;
		yes.drawButton() ;
		no.drawButton() ;
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
			back.drawButton();
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
		back.drawButton() ;
		mod1.drawButton();
		mod2.drawButton();
		glutSwapBuffers();
	}
    if(mode == GAME_MODE_2){
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,10.0f,0,0,0,0,1,0);
        _1p.drawCharacter();
        _2p.drawCharacter();
        _1pMirror.drawMirror();
        _2pMirror.drawMirror();
        margin1.drawMirror();
        margin2.drawMirror();
        margin3.drawMirror();
        margin4.drawMirror();
        
        if(BulletGeneratorStart)
        {
            for(int i = 1 ; i <= 3  ; i++)
            {
                if(BulletForHockey[i]->live)
                    BulletForHockey[i]->drawBullet();
            }
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
			back.drawButton();
		}
        glutSwapBuffers();
    }
    if(mode == GAME_RED_WIN)
    {
        redWin.drawButton();
		back.drawButton();      
		glutPostRedisplay();  
        glutSwapBuffers();
    }
    if(mode == GAME_BLUE_WIN)
    {
        blueWin.drawButton();
		back.drawButton();	
		glutPostRedisplay();  
        glutSwapBuffers();
    }
}
void Mouse(int button, int state, int x, int y){
	if(mode == GAME_MENU){
		if(start.onButton(x, y)){
			if(state == 0){
				start.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay(); 
				glutSwapBuffers();
			}
			if(state == 1){
				mode = GAME_MODE_SELECT;
				glutPostRedisplay();
				cout << "game start\n";
			}
		}
		else if(tutorial.onButton(x, y)){ // help
			if(state == 0){
				tutorial.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state){
				mode = GAME_TUTORIAL ;
				glutPostRedisplay() ;
			}
		}
		else if(quit.onButton(x, y)){ // help
			if(state == 0){
				quit.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state){
					mode = GAME_CLOSE ;
					glutPostRedisplay();
			}
		}
	}
	else if(mode == GAME_TUTORIAL)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		if(back.onButton(x, y))
		{
			if(state == 0)
			{
				back.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				mode = GAME_MENU ;
				glutPostRedisplay() ;
			}
		}
		glEnd();
		glutSwapBuffers();
	}
	else if(mode == GAME_CLOSE)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);   //??????
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1,1,1);
		gluLookAt(0,0,10.0f,0,0,0,0,1,0); 
		if(yes.onButton(x, y))
		{
			if(state == 0)
			{
				yes.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				glutDestroyWindow(glutCreateWindow(GAME_NAME));
			}
		}
		else if(no.onButton(x, y))
		{
			if(state == 0)
			{
				no.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				mode = GAME_MENU ;
				glutPostRedisplay();
			}
		}
		glEnd();
		glutSwapBuffers();
	}
	else if(mode == GAME_MODE_SELECT){
		if(mod1.onButton(x, y)){
			if(state == 0)
			{
				mod1.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				mode = GAME_MODE_1;
				_1p.init();
				_2p.init();
				_1pMirror.init();
				_2pMirror.init();
				glutPostRedisplay();
			}
		}
		if(mod2.onButton(x, y)){
			if(state == 0)
			{
				mod2.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				mode = GAME_MODE_2;
				_1p.init();
				_2p.init();
				_1pMirror.init();
				_2pMirror.init();
				glutPostRedisplay() ;
			}
		}
		if(x > START_BUTTON_LEFT + 386 && x < START_BUTTON_RIGHT + 386  && y > START_BUTTON_BOT + 268 && y < START_BUTTON_UP + 268 )
		{
			if(state == 0)
			{
				back.clicked();
				PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				glutPostRedisplay();
				glutSwapBuffers();
			}
			if(state)
			{
				mode = GAME_MENU ;
				glutPostRedisplay() ;
			}
		}
	}
	else if(mode == GAME_MODE_1){
		if(gamePause && back.onButton(x, y)){
			back.clicked();
			mode = GAME_MENU;
			gamePause = false;
			glutPostRedisplay();
			glutSwapBuffers();
		}
	}
	else if(mode == GAME_MODE_2){
		if(gamePause && back.onButton(x, y)){
			back.clicked();
			mode = GAME_MENU;
			gamePause = false;
			glutPostRedisplay();
			glutSwapBuffers();
		}
	}
	else if(mode == GAME_RED_WIN){
		if(back.onButton(x, y)){
			back.clicked();
			mode = GAME_MENU;
			gamePause = false;
			glutPostRedisplay();
			glutSwapBuffers();
		}
	}
	else if(mode == GAME_BLUE_WIN){
		if(back.onButton(x, y)){
			back.clicked();
			mode = GAME_MENU;
			gamePause = false;
			glutPostRedisplay();
			glutSwapBuffers();
		}
	}
	glutPostRedisplay();
	glutSwapBuffers();
	
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
    if(mode == GAME_MODE_2)
    {
        switch(key){
                //3 ;start game
            case('3'):
                BulletForHockey = BulletGenerator(3);
                BulletGeneratorStart = true;
                glutPostRedisplay();
                keyStates['3'] = true;
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
    //a:1p propel toward mirror
    //u:2p propel toward mirror
	if(mode == GAME_MODE_1){
		switch(key){
	        case('a'):
	            _1p.moveTowardMirror(_1pMirror);
	            glutPostRedisplay();
	            keyStates['a'] = false;
	            break;
	        case('u'):
	            _2p.moveTowardMirror(_2pMirror);
	            glutPostRedisplay();
	            keyStates['u'] = false;
	            break;
	            
	        default:
	            keyStates[key] = false;
	            break;
		}
	}
    if(mode == GAME_MODE_2)
    {
        switch(key){
            case('a'):
                _1p.moveTowardMirror(_1pMirror);
                glutPostRedisplay();
                keyStates['a'] = false;
                break;
            case('u'):
                _2p.moveTowardMirror(_2pMirror);
                glutPostRedisplay();
                keyStates['u'] = false;
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
    if(mode == GAME_MODE_1 && !gamePause){
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
	    glutPostRedisplay();
	}
    if(mode == GAME_MODE_2 && !gamePause){
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
        //
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
        if(BulletGeneratorStart)
        {
            for(int i = 1 ; i <= 3 ; i++)
            {
                BulletForHockey[i]->move();
                BulletForHockey[i]->reflect(_1pMirror);
                BulletForHockey[i]->reflect(_2pMirror);
                BulletForHockey[i]->reflect(margin1);
                BulletForHockey[i]->reflect(margin2);
                BulletForHockey[i]->reflect(margin3);
                BulletForHockey[i]->reflect(margin4);
                if(abs(BulletForHockey[i]->get_x() - _2p.get_x()) < CHAR_WIDTH / 2 + BulletSize * 1.5 && abs(BulletForHockey[i]->get_y() - _2p.get_y()) < CHAR_HEIGHT / 2 + BulletSize * 1.5){
                    if(BulletForHockey[i]->live){
                        _2p.healthP -= BulletForHockey[i]->get_atk();
                        cout << "1P: " << _1p.healthP << " 2P: " << _2p.healthP << endl;
                        BulletForHockey[i]->live = false;
                    }
                }
                if(abs(BulletForHockey[i]->get_x() - _1p.get_x()) < CHAR_WIDTH / 2 + BulletSize * 1.5 && abs(BulletForHockey[i]->get_y() - _1p.get_y()) < CHAR_HEIGHT / 2  + BulletSize * 1.5){
                    if(BulletForHockey[i]->live){
                        _1p.healthP -= BulletForHockey[i]->get_atk();
                        cout << "1P: " << _1p.healthP << " 2P: " << _2p.healthP << endl;
                        BulletForHockey[i]->live = false;
                    }
                }   
				
            }
			//i want to stop the game
            int count = 0;
            for(int i = 1 ; i <= 3 ; i++)
            {
                if(BulletForHockey[i]->live == false)
                    count++;
            }
            //need to modified (connect to endgame page)
             if(count == 3)//bullet have all disappeared now we can end game
             {
             if(_1p.healthP > _2p.healthP) //
             	mode = GAME_RED_WIN;
             else
             	mode = GAME_BLUE_WIN;
             BulletGeneratorStart = false;
             }
             
        } 
	    glutPostRedisplay();
	}
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
