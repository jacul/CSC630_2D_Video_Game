//
//  main.cpp
//  CSC630_2D_Video_Game
//  
//  author@ xiangdong zhu
//
//  Copyright  All rights reserved.
//

#include "Thing.h"
#include "Layer.h"
#include "Bomb.h"

#include <stdlib.h>			// standard definitions
#include <stdio.h>			// C I/O (for sprintf) 
#include <math.h>			// standard definitions
#include <list.h>

#ifdef _WIN32
#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#else
#include <GLUT/glut.h>			// GLUT
#include <OpenGL/glu.h>			// GLU
#include <OpenGL/gl.h>			// OpenGL
#endif


#define PAUSE 0
#define RUN   1

int game_status=PAUSE;
int width = 500;
int height = 500;

Layer layer[6];
int score;

void initGameObject(){
    layer[0] = Layer();
    layer[0].generateThings();
    
}

void customInit(){
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    
    game_status=RUN;
    
    initGameObject();
}

void reshape(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 500, 0);
    glMatrixMode(GL_MODELVIEW);
    
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 1);
    glVertex2f(15, 1);
    glVertex2f(15, 15);
    glVertex2f(1, 15);
    glEnd();
    
    glFlush();
    
    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y){
    switch (c) {
        case 'q':
            exit(0);
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void timerfunc(int status){
    if(status == RUN){
        
    }
    
    glutTimerFunc(1000, timerfunc, game_status);
}

void thingSpawn(){
    
}

void thingsMove(){
    for (int i=0; i<6; i++) {
        layer[i].thingsMovement();
    }
}

void detectCollision(){
    
}

int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    //*  Here to initial window
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Bomb Game");
    
    //Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timerfunc, PAUSE);
    
    customInit();
    
    glutMainLoop();
    
    return 0;
}