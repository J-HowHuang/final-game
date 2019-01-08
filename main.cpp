#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h> 
#include <GL\glut.h>//??DevC++??????? #include <GL\openglut.h>
#include <cstring>
#include <cmath>
#include "game.h"
using namespace std;

void WindowSize(int , int );            //????????????
void Keyboard(unsigned char , int, int );   //??????
void KeyboardUp(unsigned char, int, int);
void Display(void);                     //??
void Timer(int);
void ShootTimer(int);
//
Character _1p(CHAR_WIDTH,360, 1);
Character _2p(MAP_WIDTH - CHAR_WIDTH, 360, 2);
Mirror _1pMirror(MAP_WIDTH - CHAR_WIDTH, CHAR_HEIGHT, 1, 50);
Mirror _2pMirror(CHAR_WIDTH, MAP_HEIGHT - CHAR_HEIGHT, 2, 50);
Mirror margin1(MAP_WIDTH / 2, 3, 0, MAP_WIDTH, UP);
Mirror margin2(MAP_WIDTH / 2, MAP_HEIGHT - 3, 0, MAP_WIDTH, DOWN);
Mirror margin3(3, MAP_HEIGHT / 2, 0, MAP_HEIGHT, LEFT);
Mirror margin4(MAP_WIDTH - 3, MAP_HEIGHT / 2, 0, MAP_HEIGHT, RIGHT);
Obstacle **tree = new Obstacle *[5];
int tree_count = 2;
bool keyStates[256] = {0};
const char GAME_NAME[] = {"awesome game"};
int main(int argc, char** argv)
{
    tree[1] = new Obstacle(500,360,500 + OBSTACLE_WIDTH,360 + OBSTACLE_WIDTH);
    tree[2] = new Obstacle(200,100,200 + OBSTACLE_WIDTH,100 + OBSTACLE_WIDTH);
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
    tree[1]->drawObstacle();
    tree[2]->drawObstacle();
    _1pMirror.drawMirror();
    _2pMirror.drawMirror();
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
    
    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch(key){
            //1p character moving
            /*    case('w'):
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
             break;*/
            // shoot
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
        case('2'):
            _1p.moveTowardMirror(_1pMirror);
            glutPostRedisplay();
            keyStates['2'] = true;
            break;
        case('1'):
            _2p.moveTowardMirror(_2pMirror);
            glutPostRedisplay();
            keyStates['1'] = true;
            break;
            
        default:
            keyStates[key] = true;
            break;
    }
}
void KeyboardUp(unsigned char key, int x, int y){
    switch(key){
            //1p character moving
            /*    case('w'):
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
             break;*/
        default:
            keyStates[key] = false;
            break;
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
void Timer(int){
    /*    if(keyStates['w'] == true)
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
     _2p.move(RIGHT);*/
    
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
