#include "game.h"
#include <GL\glut.h>

Character::Character(double x, double y, int playerID){
	if(playerID == 1){
		position_x = x;
		position_y = y;
		id = 1;
		direction = RIGHT;
		speed = 10;
		moving = false;
	}
	else if(playerID == 2){
		position_x = x;
		position_y = y;
		id = 2;
		direction = LEFT;
		speed = 10;
		moving = false;
	}
}
void Character::drawCharacter(){
	if(id == 1)
		glColor3f(1.0, 0.0, 0.0);
	else if(id == 2)
		glColor3f(0.0, 0.0, 1.0);
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
void Character::shoot(){
	
}
Bullet::Bullet(double x, double y, int direct){
	
}
Character::~Character(){
	
}
