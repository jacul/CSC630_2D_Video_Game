//
//  Thing.cpp
//  CSC630_2D_Video_Game
//
// This is the thing class, it is abstract. It has two subclass,  GoodThing and BadThing.
// Thing looks like a square, and its color depends on it's type and level.
// It can be destroyed by a bomb.
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
    spd=rand()%6+3;//3~8
    dead = false;
    deadcounter=0;
}

void Thing::paint(){
    if(!dead){
        glColor3fv(THINGCOLORS[z]);
        glBegin(GL_POLYGON);
        glVertex2i(x-HALFSIZE, y-HALFSIZE); // The bottom left corner  
        glVertex2i(x-HALFSIZE, y+HALFSIZE); // The top left corner  
        glVertex2i(x+HALFSIZE, y+HALFSIZE); // The top right corner  
        glVertex2i(x+HALFSIZE, y-HALFSIZE); // The bottom right corner  
        glEnd();
    }else{
        glColor3f(0,0,1);
        glBegin(GL_LINE_STRIP);
        glVertex2i(x-HALFSIZE, y-HALFSIZE); // The bottom left corner  
        glVertex2i(x-HALFSIZE, y+HALFSIZE); // The top left corner  
        glVertex2i(x+HALFSIZE, y+HALFSIZE); // The top right corner  
        glVertex2i(x+HALFSIZE, y-HALFSIZE); // The bottom right corner
        glVertex2i(x-HALFSIZE, y-HALFSIZE);
        glEnd();
    }
}

void Thing::move(){
    float dg=r*DR;
    x+= cos(dg)*spd;
    y-= sin(dg)*spd;
    if(x<HALFSIZE){
        x=HALFSIZE;
        r=180-r;
    }else if(x>399-HALFSIZE){
        x=399-HALFSIZE;
        r=180-r;
    }
    if(y<HALFSIZE){
        y=HALFSIZE;
        r=360-r;
    }else if(y>399-HALFSIZE){
        y=399-HALFSIZE;
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