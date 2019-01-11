#include <GL\glut.h>
#include <string>
#include <GL\freeglut.h> 
#ifndef _BUTTON_H
#define _BUTTON_H
#define MAX_BUTTON_NAME_LENGTH 50
class Button{
	private:
		double position_x; // x coord of left bot point
		double position_y; // y coord of left bot point
		double width;
		double height;
		GLuint id;
		char* name;
	public:
		Button(char* buttonName, double x, double y, double width, double height);
		~Button();
		void drawButton();
		bool onButton(double x, double y);
		void clicked();
		
};

#endif
