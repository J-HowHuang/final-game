#include "game.h"
#include <GL\glut.h>

Character::Character(double x, double y, int playerID){
	if(playerID == 1){
		position_x = x;
		position_y = y;
		id = 1;
		direction = RIGHT;
		speed = 10;
	}
	else if(playerID == 2){
		position_x = x;
		position_y = y;
		id = 2;
		direction = LEFT;
		speed = 10;
	}
}
void Character::drawCharacter(){
	glColor3f(1.0, 0.0, 0.0);
	glRectd(position_x - 20, position_y - 20, position_x + 20, position_y + 20);
}
void Character::moveStep(){
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
Character::~Character(){
	
}
