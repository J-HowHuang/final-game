#ifndef _GAME_H
#define _GAME_H

#define default_x_1p 30
#define default_y_1p 30
#define MAP_WIDTH 1080
#define MAP_HEIGHT 720
#define CHAR_WIDTH 40
#define CHAR_HEIGHT 40
#define FPS 30

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
		Character(double x, double y, int playerID);
		~Character();
		void drawCharacter();
		int getDirection(){return direction;}
		void setDirection(int direct){direction = direct;}
		void move(int direct);
		double get_x(){return position_x;}
		double get_y(){return position_y;}
		bool moving;
		void shoot();
};
class Bullet{
	private:
		double speed;
		int direction;
		double power;
		double position_x;
		double position_y;
	public:
		Bullet(double x, double y);
		terminate();
		~Bullet();
};
#endif
