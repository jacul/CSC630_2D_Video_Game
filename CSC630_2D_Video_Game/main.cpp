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

Layer layer[LAYERNUM];
list<Bomb> bombs;

int score;
int counter;

void thingSpawn();
void thingsMove();
void detectCollision();

void initGameObject(){
//TODO: more initialize
    thingSpawn();
}

void customInit(){
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    
    game_status=RUN;
    counter=0;
    score=0;
    
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

void dropBomb(int x,int y){
    Bomb b(x,y,0);
    bombs.push_back(b);
}

void mouse(int button,int status,int x,int y){
    if(status==GLUT_UP){
        switch (button) {
            case GLUT_LEFT_BUTTON:
                dropBomb(x*500/width, y*500/width);
                break;
                
            default:
                break;
        }
    }
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
        thingsMove();
        detectCollision();
    }
    //for debug purpose
    list<Bomb>::iterator it;
    for(it=bombs.begin();it!=bombs.end();it++){
        it->paint();
    }
    for (int i=0; i<LAYERNUM; i++) {
        layer[i].drawThings();
    }
    cout<<"one loop========"<< counter++ <<endl;
    glutTimerFunc(1000, timerfunc, game_status);
}

void thingsMove(){
    for (int i=0; i<LAYERNUM; i++) {
        layer[i].thingsMovement();
    }
    
    list<Bomb>::iterator it;
    for(it=bombs.begin(); it!=bombs.end(); it++){
        if(it->forwardToBottom()){
//TODO: any problems here?
            cout<<"erase"<<endl;
            bombs.erase(it);
        }
    }
    
}

void detectCollision(){
    
}

void thingSpawn(){
    layer[3].generateThings(BAD);
    layer[4].generateThings(BAD);
}

int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //*  Here to initial window
    glutInitWindowSize(width, height);
    glutInitWindowPosition(400, 200);
    glutCreateWindow("Bomb Game");
    
    //Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(1000, timerfunc, PAUSE);
    
    customInit();
    
    glutMainLoop();
    
    return 0;
}