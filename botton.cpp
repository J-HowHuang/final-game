#include <GL\glut.h>
#include <cmath>
#include<windows.h>
#include<Mmsystem.h>
#include "button.h"
#include "bitmap.h"
#include <cstring>
void buttonLoadTexture(char*, GLuint);
Button::Button(char* buttonName, double  x, double y, double _width, double _height){
	name = new char[MAX_BUTTON_NAME_LENGTH];
	strcpy(name, buttonName);
	strcat(name, ".bmp");
	position_x = x;
	position_y = y;
	width = _width ;
	height = _height ;
}
void Button::drawButton(){
	buttonLoadTexture(name, id);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2f(position_x, position_y);
		glTexCoord2f(0, 1); glVertex2f(position_x, position_y + height);
		glTexCoord2f(1, 1); glVertex2f(position_x + width, position_y + height);
		glTexCoord2f(1, 0); glVertex2f(position_x + width, position_y);
	glEnd();
}
bool Button::onButton(double x, double y){
	if(x > position_x && x < position_x + width && y > position_y && y < position_y + height)
		return true;
	else
		return false;
}
void Button::clicked(){
	char* filename = new char[MAX_BUTTON_NAME_LENGTH];
	filename = strcat(name, "_clicked.bmp");
	buttonLoadTexture(filename, id);
	glBindTexture(GL_TEXTURE_2D, id);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 0); glVertex2f(position_x, position_y);
		glTexCoord2f(0, 1); glVertex2f(position_x, position_y + height);
		glTexCoord2f(1, 1); glVertex2f(position_x + width, position_y + height);
		glTexCoord2f(1, 0); glVertex2f(position_x + width, position_y);
	glEnd();
	PlaySound(TEXT("C:\\click.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
Button::~Button(){
	
}
void buttonLoadTexture(char* filename, GLuint id){
	BmpLoader image(filename);
	glGenTextures(1, &id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.iWidth, image.iHeight, GL_RGB, GL_UNSIGNED_BYTE, image.TextureData);
}
