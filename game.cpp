#include "game.h"
#include <GL\glut.h>
#include <cmath>
Bullet::Bullet(double x, double y, int direction_,int playerID)
{
    
    bullet_size = 12 ;
    if(playerID == 1)
    {
        position_x = x;
        position_y = y;
        id = 1;
        direction = direction_;
        speed = 20;
        attack = 10;
        live = true;
    }
    else if(playerID == 2)
    {
        position_x = x;
        position_y = y;
        id = 2;
        direction = direction_;
        speed = 20;
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
    if(direction == UP){
        position_y += speed;
    }
    else if(direction == DOWN){
        position_y -= speed;
    }
    else if(direction == RIGHT){
        position_x += speed;
    }
    else if(direction == LEFT){
        position_x -= speed;
    }
}
Character::Character(double x, double y, int playerID){
	if(playerID == 1){
		healthP = 100;
		position_x = x;
		position_y = y;
		id = 1;
		direction = RIGHT;
		speed = 10;
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
		speed = 10;
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
	if(direction == UP)
		glRectd(position_x - 6, position_y + 20, position_x + 6, position_y + 32);
	if(direction == DOWN)
		glRectd(position_x + 6, position_y - 20, position_x - 6, position_y - 32);
	if(direction == RIGHT)
		glRectd(position_x + 20, position_y - 6, position_x + 32, position_y + 6);
	if(direction == LEFT)
		glRectd(position_x - 20, position_y + 6, position_x - 32, position_y - 6);
}
void Character::move(int direct){
	if(direct == UP){
		position_y += speed;
	}
	else if(direct == DOWN){
		position_y -= speed;
	}
	else if(direct == RIGHT){
		position_x += speed;
	}
	else if(direct == LEFT){
		position_x -= speed;
	}
}
void Character::shoot(int BulletCount)
{
    if(direction == UP)
        pBullet[BulletCount] = new Bullet(position_x,position_y + 26,direction,id);
    if(direction == DOWN)
        pBullet[BulletCount] = new Bullet(position_x,position_y - 26,direction,id);
    if(direction == RIGHT)
        pBullet[BulletCount] = new Bullet(position_x + 26,position_y,direction,id);
    if(direction == LEFT)
        pBullet[BulletCount] = new Bullet(position_x - 26,position_y,direction,id);
    addBulletCount();
}
Mirror::Mirror(double x, double y, int playerID){
	if(playerID == 1){
		position_x = x;
		position_y = y;
		id = 1;
		direction = UP_LEFT;
		speed = 10;
		moving = false;
	}
	else if(playerID == 2){
		position_x = x;
		position_y = y;
		id = 2;
		direction = DOWN_RIGHT;
		speed = 10;
		moving = false;
	}
}
void Mirror::drawMirror(){
	if(id == 1)
		glColor3f(1, 0, 0);
	else if(id == 2)
		glColor3f(0, 0, 1);
	if(direction == UP_RIGHT){
		glLineWidth(3 * sqrt(2));
			glBegin(GL_LINES);
				glVertex2f(position_x - 20, position_y + 20);
				glVertex2f(position_x + 20, position_y - 20);
			glEnd();
		glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y - 20);
				glVertex2f(position_x - 20, position_y - 20);
				glVertex2f(position_x - 20, position_y - 20);
				glVertex2f(position_x - 20, position_y + 20);
			glEnd();
	}
	else if(direction == UP_LEFT){
		glLineWidth(3 * sqrt(2));
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x - 20, position_y - 20);
			glEnd();
		glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x + 20, position_y - 20);
				glVertex2f(position_x + 20, position_y - 20);
				glVertex2f(position_x - 20, position_y - 20);
			glEnd();
	}
	else if(direction == DOWN_RIGHT){
		glLineWidth(3 * sqrt(2));
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x - 20, position_y - 20);
			glEnd();
		glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x - 20, position_y + 20);
				glVertex2f(position_x - 20, position_y + 20);
				glVertex2f(position_x - 20, position_y - 20);
			glEnd();
	}
	else if(direction == DOWN_LEFT){
		glLineWidth(3 * sqrt(2));
			glBegin(GL_LINES);
				glVertex2f(position_x - 20, position_y + 20);
				glVertex2f(position_x + 20, position_y - 20);
			glEnd();
		glLineWidth(3);
			glBegin(GL_LINES);
				glVertex2f(position_x + 20, position_y - 20);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x + 20, position_y + 20);
				glVertex2f(position_x - 20, position_y + 20);
			glEnd();
	}
}
void Mirror::move(int direct){
	if(direct == UP){
		position_y += speed;
	}
	else if(direct == DOWN){
		position_y -= speed;
	}
	else if(direct == RIGHT){
		position_x += speed;
	}
	else if(direct == LEFT){
		position_x -= speed;
	}
}
void Mirror::rotate(int tao){
	if(tao > 0){
		switch(direction){
			case(UP_LEFT):
				direction = DOWN_LEFT;
				break;
			case(DOWN_LEFT):
				direction = DOWN_RIGHT;
				break;
			case(DOWN_RIGHT):
				direction = UP_RIGHT;
				break;
			case(UP_RIGHT):
				direction = UP_LEFT;
				break;
		}
	}
	if(tao < 0){
		switch(direction){
			case(UP_LEFT):
				direction = UP_RIGHT;
				break;
			case(DOWN_LEFT):
				direction = UP_LEFT;
				break;
			case(DOWN_RIGHT):
				direction = DOWN_LEFT;
				break;
			case(UP_RIGHT):
				direction = DOWN_RIGHT;
				break;
		}
	}
}
Mirror::~Mirror(){
	
}
Character::~Character(){
	
}
Bullet::~Bullet()
{
    
}
