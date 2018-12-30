#include "game.h"
#include <GL\glut.h>

Character::Character(double x, double y, int playerID){
	if(playerID == 1){
		position_x = 30;
		position_y = 30;
		id = 1;
		direction = RIGHT;
	}
	else if(playerID == 2){
		position_x = MAP_WIDTH - CHAR_WIDTH - 30;
		position_y = MAP_HEIGHT - CHAR_HEIGHT - 30;
		id = 2;
		direction = LEFT;
	}
}
void Character::drawCharacter(){
	glColor3f(1.0, 0.0, 0.0);
	glRectd(position_x, position_y, position_x + 40, position_y + 40);
}
Character::~Character(){
	
}
