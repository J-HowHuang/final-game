#include "game.h"
#include <GL\glut.h>
#include <cmath>
Bullet::Bullet(double x, double y, double direction_,int playerID)
{
    
    bullet_size = BulletSize ;
    if(playerID == 1)
    {
        position_x = x;
        position_y = y;
        id = 1;
        direction = direction_;
        speed = 7;
        attack = 1;
        live = true;
    }
    else if(playerID == 2)
    {
        position_x = x;
        position_y = y;
        id = 2;
        direction = direction_;
        speed = 7;
        attack = 1;
        live = true;
    }
}
void Bullet::drawBullet()
{
    
    if(id == 1)
    {
        //glColor3f(1.0, .0, .0);
        //glRectd(position_x - bullet_size / 2 , position_y - bullet_size / 2, position_x + bullet_size / 2, position_y + bullet_size / 2);
        glBegin(GL_POLYGON);
        glColor3f(1.0, .0, .0);
        for(int i = 1 ; i <= 24 ; i++ )
        {
            glVertex2f(position_x + bullet_size / 2 * cos(2 * PI/24 * i), position_y + bullet_size / 2 * sin(2 * PI/24 * i));
            //glTexCoord2f(position_x + cos(PI/24 * i), position_y + sin(PI/24 * i));
        }
        glEnd();
    }
    else if(id == 2)
    {
        //glColor3f(.0, .0, 1.0);
        //glRectd(position_x - bullet_size / 2 , position_y - bullet_size / 2, position_x + bullet_size / 2, position_y + bullet_size / 2);
        glBegin(GL_POLYGON);
        glColor3f(.0, .0, 1.0);
        for(int i = 1 ; i <= 24 ; i++ )
        {
            glVertex2f(position_x + bullet_size / 2 * cos(2 * PI/24 * i), position_y + bullet_size / 2 * sin(2 * PI/24 * i));
            //glTexCoord2f(position_x + cos(PI/24 * i), position_y + sin(PI/24 * i));
        }
        glEnd();
    }
}
void Bullet::move(){
    position_y += speed * sin(direction);
    position_x += speed * cos(direction);
}
void Bullet::reflect(Mirror& mirr){
    if(this->OnMirror(position_x, position_y, mirr.get_x(), mirr.get_y(), mirr.getSize(), mirr.getDirection())){
        direction = 2 * mirr.getDirection() - direction + PI;
    }
}
bool Bullet::OnMirror(int x,int y,int mx,int my, int l, double theta)
{
    double DisToVertex = (x - mx) * (x - mx) + (y - my) * (y - my);
    if(DisToVertex > (l/2 + 20) * (l/2 + 20))
        return false;
    double line = mx + my * tan(theta);
    double DisToLine = abs(x + y * tan(theta)- line)/sqrt(1 + tan(theta) * tan(theta));
    if(abs(DisToLine) < BulletSize/2 )
        return true;
    else
        return false;
}
void Bullet::getInObstacle(Obstacle O1)
{
    double mid_x = (O1.coodLD_x + O1.coodRT_x)/2;
    double mid_y = (O1.coodLD_y + O1.coodRT_y)/2;
    double DisToVertex = (position_x - mid_x) * (position_x - mid_x) + (position_y - mid_y) * (position_y - mid_y);
    double diameter = (O1.coodLD_x - mid_x) * (O1.coodLD_x - mid_x) + (O1.coodLD_y - mid_y) * (O1.coodLD_y - mid_y);
    if(DisToVertex <= diameter )
    {
        if((position_x - O1.coodRT_x) < BulletSize/2)
            live = false;
        if((O1.coodLD_x - position_x) < BulletSize/2)
            live = false;
        if((position_y - O1.coodRT_y) < BulletSize/2)
            live = false;
        if((O1.coodLD_y - position_y) < BulletSize/2)
            live = false;
    }
    
    
    
}
Character::Character(double x, double y, int playerID){
    if(playerID == 1){
        healthP = 100;
        position_x = x;
        position_y = y;
        id = 1;
        direction = RIGHT;
        speed = 0;
        angV = PI / FPS / 2;
        moving = false;
        pBullet = new Bullet*[MAX_BULLET_ON_PLANE];
        bulletCount = 0;
    }
    else if(playerID == 2){
        healthP = 100;
        position_x = x;
        position_y = y;
        id = 2;
        direction = LEFT;
        speed = 0;
        angV = PI / FPS / 2;
        moving = false;
        pBullet = new Bullet*[MAX_BULLET_ON_PLANE];
        bulletCount = 0;
    }
}
void Character::drawCharacter(){
    if(id == 1)
        glColor3f(1.0, 0.0, 0.0);
    else if(id == 2)
        glColor3f(0.0, 0.0, 1.0);
    //change number to constant
    glRectd(position_x - 20, position_y - 20, position_x + 20, position_y + 20);
    glLoadIdentity();
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2f(position_x, position_y);
    glVertex2f(position_x + cos(direction) * 35, position_y + sin(direction) * 35);
    glEnd();
}
void Character::move(){
    //position_y += speed * sin(direct);
    //position_x += speed * cos(direct);
    position_x += (aim_position_x - position_x) / times;
    position_y += (aim_position_y - position_y) / times;
}
void Character::rotate(int tao){
    if(tao > 0){
        direction += angV;
    }
    if(tao < 0){
        direction -= angV;
    }
}
void Character::shoot(int BulletCount)
{
    pBullet[BulletCount] = new Bullet(position_x,position_y,direction,id);
    addBulletCount();
}
void Character::moveTowardMirror(Mirror player)
{
    double rate = 0.5;
    aim_position_x = (position_x + player.get_x()) * rate;
    aim_position_y = (position_y + player.get_y()) * rate;
    
    double distanceSquare = ( aim_position_x - position_x ) * ( aim_position_x - position_x ) + ( aim_position_y - position_y ) * ( aim_position_y - position_y );
    speed = 15;
    times = sqrt(distanceSquare)/speed + 1;
}

Mirror::Mirror(double x, double y, int playerID, double _size, double _direction){
    if(playerID == 1){
        position_x = x;
        position_y = y;
        id = 1;
        direction = UP_LEFT;
        speed = 3;
        angV = PI / FPS / 2;
        moving = false;
        reflectable = true;
        size = _size;
    }
    else if(playerID == 2){
        position_x = x;
        position_y = y;
        id = 2;
        direction = DOWN_RIGHT;
        speed = 3;
        angV = PI / FPS / 2;
        moving = false;
        reflectable = true;
        size = _size;
    }
    else{
        position_x = x;
        position_y = y;
        id = 0;
        direction = _direction;
        speed = 0;
        angV = 0;
        moving = false;
        reflectable = true;
        size = _size;
    }
}
void Mirror::drawMirror(){
    if(id == 1)
        glColor3f(1, 0, 0);
    else if(id == 2)
        glColor3f(0, 0, 1);
    else
        glColor3f(0, 0, 0);
    
    glLineWidth(3 * sqrt(2));
    glBegin(GL_LINES);
    glVertex2f(position_x + size * cos(direction - PI / 2), position_y + size * sin(direction - PI / 2));
    glVertex2f(position_x - size * cos(direction - PI / 2), position_y - size * sin(direction - PI / 2));
    glEnd();
    
    
}
void Mirror::move(double direct){
    position_y += speed * sin(direct);
    position_x += speed * cos(direct);
}
void Mirror::rotate(int tao){
    if(tao > 0){
        direction += angV;
    }
    if(tao < 0){
        direction -= angV;
    }
}
bool Mirror::disToObstacle(Obstacle OB)
{
    double length = (size + (OB.coodRT_x - OB.coodLD_x))/2;
    double dis = (position_x - (OB.coodRT_x + OB.coodLD_x)/2)*(position_x - (OB.coodRT_x + OB.coodLD_x)/2) + (position_y - (OB.coodRT_y + OB.coodLD_y)/2)*(position_y - (OB.coodRT_y + OB.coodLD_y)/2);
    
    if(dis < length * length )
        return true;
    else
        return false;
}
Obstacle::Obstacle(double LD_x, double LD_y,double RT_x,double RT_y)
{
    coodLD_x = LD_x;
    coodLD_y = LD_y;
    coodRT_x = RT_x;
    coodRT_y = RT_y;
}
void Obstacle::drawObstacle()
{
    glColor3f(.0, .0, .0);
    glRectd(coodLD_x,coodLD_y , coodRT_x, coodRT_y);
}
Mirror::~Mirror(){
    
}
Character::~Character(){
    
}
Bullet::~Bullet()
{
    
}
Obstacle::~Obstacle()
{
    
}
