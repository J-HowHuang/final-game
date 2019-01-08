#ifndef _GAME_H
#define _GAME_H

#define default_x_1p 30
#define default_y_1p 30
#define MAP_WIDTH 1080
#define MAP_HEIGHT 720
#define CHAR_WIDTH 60
#define CHAR_HEIGHT 60
#define CANNON_LENGTH 45
#define MIRROR_SIZE 60
#define MIRROR_WIDTH 12
#define FPS 120
#define MAX_BULLET_ON_PLANE 25000
#define DEFAULT_SHOOTING_SPEED exp(1)
#define MIRROR_OFFSET 0
#define PI 3.14159

#define UP PI / 2
#define DOWN -PI / 2
#define LEFT PI
#define RIGHT 0
#define DOWN_LEFT -3 * PI / 4
#define DOWN_RIGHT -PI / 4
#define UP_LEFT PI / 4
#define UP_RIGHT 3 * PI / 4

#define START_BUTTON_LEFT MAP_WIDTH / 2 - 172
#define START_BUTTON_RIGHT = MAP_WIDTH / 2 + 172;
#define START_BUTTON_UP  MAP_HEIGHT / 2 + 64;
#define START_BUTTON_BOTy  MAP_HEIGHT / 2 - 64;
#define GAME_MENU 1
#define GAME_MODE_1 2
#define GAME_MODE_2 3
#define GAME_SETTING 4
#define GAME_RESULT 5
class Mirror{
	private:
		double position_x;
		double position_y;
		double direction;
		int id;
		double speed;
		double angV;
		double size;
	public:
		Mirror(double x, double y, int playerID, double size, double direction = 0);
		~Mirror();
		void drawMirror();
		void move(double direct);
		void rotate(int tao);
		bool moving;
		bool reflectable;
		double get_x(){return position_x;}
		double get_y(){return position_y;}
		void set_x(double x){position_x = x;}
		void set_y(double y){position_y = y;}
		double getDirection(){return direction;}
		void setDirection(double direct){direction = direct;}
		double getSize(){return size;}
};
class Bullet{
private:
    double speed;
    double direction;
    int id;
    double power;
    double position_x;
    double position_y;
    int bullet_size;
    double attack;
public:
    Bullet(double x, double y,double direction, int playerID);
    ~Bullet();
    void drawBullet();
    void move();
    double get_x(){return position_x;}
    double get_y(){return position_y;}
    double get_atk(){return attack;}
    bool OnMirror(int x,int y,int mx,int my, int l,double theta);// here
    void reflect(Mirror& mirr);// here
    bool live;
};
class Character{
	private:
		double speed;
		double power;
		double direction;
		int id;
		double position_x;
		double position_y;
		int bulletCount;
		double angV;
	public:
		Character(double x, double y, int playerID);
		~Character();
		void drawCharacter();
		double getDirection(){return direction;}
		void setDirection(double direct){direction = direct;}
		void rotate(int tao);
		void move(double direct);
		double get_x(){return position_x;}
		void set_x(double x){position_x = x;}
		void set_y(double y){position_y = y;}
		double get_y(){return position_y;}
		int getBulletCount(){return bulletCount;}
		void addBulletCount(){bulletCount++;}
		bool moving;
		void shoot(int BulletCount);
		double healthP;
		Bullet** pBullet;
};
#endif
