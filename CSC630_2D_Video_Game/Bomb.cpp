//
//  Bomb.cpp
//  CSC630_2D_Video_Game
//  Represents a bomb. It has color and shape. Becomes more and more invisible while going deeper.
//  After going to level 5, it's destroyed.
//  
//

#include "Bomb.h"
#include <iostream>

#ifdef _WIN32
#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#else
#include <GLUT/glut.h>			// GLUT
#include <OpenGL/glu.h>			// GLU
#include <OpenGL/gl.h>			// OpenGL
#endif

bool Bomb::isCollision(Thing *thing){
    int tx=thing->getX();
    int ty=thing->getY();
    return tx>=x-HALFSIZE && tx<=x+HALFSIZE && ty>=y-HALFSIZE && ty<=y+HALFSIZE;
}

//bomb is a triangle
void Bomb::paint(){
    glColor3fv(BOMBCOLORS[z]);
    glBegin(GL_POLYGON);
    glVertex2d(x, y-4);
    glVertex2d(x+4, y+4);
    glVertex2d(x-4, y+4);
    glEnd();
}

void Bomb::printInfo(){
    cout<<"Bomb at: "<<x<<" "<<y<<" "<<z<<endl;
}

//the bomb moves all the way to bottom. If it reached the bottom, the return value will be true; otherwise false.
bool Bomb::forwardToBottom(){
    z++;
    return z>=LAYERNUM;
}

int Bomb::getLevel(){
    return z;
}

//the bomb hits this level. It may kill something. Can be good or bad. Can gain score or lose score.
int Bomb::hitLevel(Layer *layer){
    int kills = 0;
    list<Thing*> *things = layer->getAllThings();
    list<Thing*>::iterator it;
    for(it=things->begin(); it!=things->end(); it++){
        if (isCollision(*it)) {
            (*it)->kill();
            kills++;
        }
    }
    return kills*layer->getLevelScore();
}