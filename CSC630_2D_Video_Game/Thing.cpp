//
//  Thing.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Thing.h"

#ifdef _WIN32
#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#else
#include <GLUT/glut.h>			// GLUT
#include <OpenGL/glu.h>			// GLU
#include <OpenGL/gl.h>			// OpenGL
#endif

void Thing::paint(){
    glPointSize(20.0f);  
    glBegin(GL_POINTS); // Start drawing a point primitive  
    glVertex2i(x, y); // The bottom left corner  
    //glVertex2i(x-1, y+1); // The top left corner  
    //glVertex2i(x+1, y+1); // The top right corner  
    //glVertex2i(x+1, y-1); // The bottom right corner  
    glEnd();
}

void Thing::move(){
    
}

void Thing::printInfo(){
    cout<<"Thing at: x:"<<x<<" y:"<<y<<" type:"<<(getThingType()==GOOD?"Good":"Bad")<<endl;
}

int BadThing::getThingType(){
    return BAD;
}

int GoodThing::getThingType(){
    return GOOD;
}