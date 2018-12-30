#include "game.h"
#include <GL\glut.h>

Character::Character(double x, double y){
	position_x = x;
	position_y = y;
}
void Character::drawCharacter(){
	glColor3f(1.0, 0.0, 0.0);
	glRectd(position_x, position_y, position_x + 3, position_y + 3);
}
Character::~Character(){
	
}
