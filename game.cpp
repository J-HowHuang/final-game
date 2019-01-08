#include "game.h"
#include <GL\glut.h>
#include <cmath>
Bullet::Bullet(double x, double y, double direction_,int playerID)
{
    
    bullet_size = 12 ;
    if(playerID == 1)
    {
        position_x = x;
        position_y = y;
        id = 1;
        direction = direction_;
        speed = 15;
        attack = 10;
        live = true;
    }
    else if(playerID == 2)
    {
        position_x = x;
        position_y = y;
        id = 2;
        direction = direction_;
        speed = 15;
        attack = 10;
        live = true;
    }
}
void Bullet::drawBullet()
{
    
    if(id == 1)
    {
        glColor3f(1.0, .0, .0);
        glRectd(position_x - bullet_size / 2 , position_y - bullet_size / 2, position_x + bullet_size / 2, position_y + bullet_size / 2);
    }
    else if(id == 2)
    {
        glColor3f(.0, .0, 1.0);
        glRectd(position_x - bullet_size / 2 , position_y - bullet_size / 2, position_x + bullet_size / 2, position_y + bullet_size / 2);
    }
}
void Bullet::move(){
    position_y += speed * sin(direction);
    position_x += speed * cos(direction);
}
void Bullet::reflect(Mirror& mirr){
	if(this->OnMirror(position_x, position_y, mirr.get_x(), mirr.get_y(), mirr.getSize(), direction)){
		direction = 2 * mirr.getDirection() - direction;
	}
}
bool Bullet::OnMirror(int x,int y,int mx,int my, int l,double theta)
{
    int DisToVertex = (x - mx) * (x - mx) + (y - my) * (y - my);
    if(DisToVertex > (l/2) * (l/2))
        return false;
    double line = mx + my * tan(theta);
    double DisToLine = abs(x + y * tan(theta)- line)/sqrt(1 + tan(theta) * tan(theta));
    if(DisToLine == 0)
        return true;
    else
        return false;
}
Character::Character(double x, double y, int playerID){
	if(playerID == 1){
		healthP = 100;
		position_x = x;
		position_y = y;
		id = 1;
		direction = RIGHT;
		speed = 3;
		moving = false;
		pBullet = new Bullet*[MAX_BULLET_ON_PLANE];
		bulletCount = 0;
	}
	else if(playerID == 2){
		healthP = 100;
		position_x = x;
		position_y = y;
		id = 2;
		direction = LEFT;
		speed = 3;
		moving = false;
		pBullet = new Bullet*[MAX_BULLET_ON_PLANE];
		bulletCount = 0;
	}
}
void Character::drawCharacter(){
	if(id == 1)
		glColor3f(1.0, 0.0, 0.0);
	else if(id == 2)
		glColor3f(0.0, 0.0, 1.0);
	//change number to constant 
	glRectd(position_x - 20, position_y - 20, position_x + 20, position_y + 20);
	glLoadIdentity();
	glLineWidth(6);
	glBegin(GL_LINES);
		glVertex2f(position_x, position_y);
		glVertex2f(position_x + cos(direction) * 35, position_y + sin(direction) * 35);
	glEnd();
}
void Character::move(double direct){
    position_y += speed * sin(direct);
    position_x += speed * cos(direct);
}
void Character::shoot(int BulletCount)
{
    pBullet[BulletCount] = new Bullet(position_x,position_y,direction,id);
    addBulletCount();
}
Mirror::Mirror(double x, double y, int playerID, double _size){
	if(playerID == 1){
		position_x = x;
		position_y = y;
		id = 1;
		direction = UP_LEFT;
		speed = 3;
		angV = PI / FPS;
		moving = false;
		reflectable = true;
		size = _size;
	}
	else if(playerID == 2){
		position_x = x;
		position_y = y;
		id = 2;
		direction = DOWN_RIGHT;
		speed = 3;
		angV = PI / FPS;
		moving = false;
		reflectable = true;
		size = _size;
	}
}
void Mirror::drawMirror(){
	if(id == 1)
		glColor3f(1, 0, 0);
	else if(id == 2)
		glColor3f(0, 0, 1);
	else
		glColor3f(0, 0, 0);
		
	glLineWidth(3 * sqrt(2));
		glBegin(GL_LINES);
			glVertex2f(position_x + size * cos(direction - PI / 2), position_y + size * sin(direction - PI / 2));
			glVertex2f(position_x - size * cos(direction - PI / 2), position_y - size * sin(direction - PI / 2));
		glEnd();

	
}
void Mirror::move(double direct){
    position_y += speed * sin(direct);
    position_x += speed * cos(direct);
}
void Mirror::rotate(int tao){
	if(tao > 0){
		direction += angV;
	}
	if(tao < 0){
		direction -= angV;
	}
}
Mirror::~Mirror(){
	
}
Character::~Character(){
	
}
Bullet::~Bullet()
{
    
}

