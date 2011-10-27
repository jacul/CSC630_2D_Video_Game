//
//  Thing.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Thing.h"
#include <math.h>
#ifdef _WIN32
#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#else
#include <GLUT/glut.h>			// GLUT
#include <OpenGL/glu.h>			// GLU
#include <OpenGL/gl.h>			// OpenGL
#endif

Thing::Thing(int x, int y, int z){
    this->x=x;this->y=y;this->z=z;
    r = rand()%361;//0~360
    spd=rand()%9+2;//2~10
}

void Thing::paint(){
    glColor3fv(COLORS[z]);
    glBegin(GL_POLYGON);
    glVertex2i(x-HALFSIZE, y-HALFSIZE); // The bottom left corner  
    glVertex2i(x-HALFSIZE, y+HALFSIZE); // The top left corner  
    glVertex2i(x+HALFSIZE, y+HALFSIZE); // The top right corner  
    glVertex2i(x+HALFSIZE, y-HALFSIZE); // The bottom right corner  
    glEnd();
}

void Thing::move(){
    float dg=r*DR;
    x+= cos(dg)*spd;
    y-= sin(dg)*spd;
    if(x<0||x>399){
        r=180-r;
    }
    if(y<0||y>399){
        r=360-r;
    }
    r%=361;
}

void Thing::printInfo(){
    cout<<"Thing at: x:"<<x<<" y:"<<y<<" z:"<<z<<" type:"<<(getThingType()==GOOD?"Good":"Bad")<<endl;
}

int BadThing::getThingType(){
    return BAD;
}

int GoodThing::getThingType(){
    return GOOD;
}