
#include <GL\glut.h>
#include <string>
#ifndef _BOTTON_H
#define _BOTTON_H
#define MAX_BOTTON_NAME_LENGTH 50
class Botton{
	private:
		double position_x; // x coord of left bot point
		double position_y; // y coord of left bot point
		double width;
		double height;
		GLuint id;
		char* name;
	public:
		Botton(char* bottonName, double x, double y, double width, double height);
		~Botton();
		void drawBotton();
		bool onBotton(double x, double y);
		void clicked();
		
};
#endif
