//
//  Bomb.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
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

void Bomb::paint(){
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2d(x, y-4);
    glVertex2d(x+4, y+4);
    glVertex2d(x-4, y+4);
    glEnd();
}

void Bomb::printInfo(){
    cout<<"Bomb at: "<<x<<" "<<y<<" "<<z<<endl;
}

bool Bomb::forwardToBottom(){
    z++;
    return z>=LAYERNUM;
}

int Bomb::getLevel(){
    return z;
}

int Bomb::hitLevel(Layer *layer){
    int kills = 0;
    list<Thing*> *things = layer->getAllThings();
    list<Thing*>::iterator it;
    for(it=things->begin(); it!=things->end(); it++){
        if (isCollision(*it)) {
            things->erase(it);
            kills++;
        }
    }
    return kills;
}