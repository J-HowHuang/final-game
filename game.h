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
#define DOWN_LEFT 3
#define DOWN_RIGHT -3
#define UP_LEFT 4
#define UP_RIGHT -4
class Bullet{
private:
    double speed;
    int direction;
    int id;
    double power;
    double position_x;
    double position_y;
    int bullet_size;
public:
    Bullet(double x, double y,int direction, int playerID);
    ~Bullet();
    void drawBullet();
    void move();
    //terminate();
};
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
		void shoot(int &BulletCount);
};
class Mirror{
	private:
		double position_x;
		double position_y;
		int direction;
		int id;
		double speed;
	public:
		Mirror(double x, double y, int playerID);
		~Mirror();
		void drawMirror();
		void move(int direct);
		void rotate(int tao);
		bool moving;
		double get_x(){return position_x;}
		double get_y(){return position_y;}
		int getDirection(){return direction;}
		void setDirection(int direct){direction = direct;}
};

#endif
