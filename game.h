#ifndef _GAME_H
#define _GAME_H

#define default_x_1p 30
#define default_y_1p 30
#define MAP_WIDTH 1080
#define MAP_HEIGHT 720
#define CHAR_WIDTH 40
#define CHAR_HEIGHT 40

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
class Character{
	private:
		double healthP;
		double speed;
		double power;
		int direction;
		int id;
		double position_x;
		double position_y;
	public:
		Character(double x, double y);
		~Character();
		void drawCharacter();
};
#endif
