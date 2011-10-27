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
#define INTERVAL 100

int game_status;
int width = 500;
int height = 500;

//five layers
Layer layer[LAYERNUM]={Layer(0),Layer(1),Layer(2),Layer(3),Layer(4)};
list <Bomb*> bombs;

int score;
int counter;

bool FULLSCREEN=false;

//every fixed time, new things appear
void thingSpawn();
//movement of the things
void thingsMove();
//check if the bomb hit the things
void detectCollision();
void quit();
void debugOutput();
//this function makes the game go one step further
void oneMovement();

void initGameObject(){
    //every level we have four things, for simplicity we just spawn four times
    thingSpawn();
    thingSpawn();
    thingSpawn();
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

//invoked when the window is resized
void reshape(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 400, 0);
    glMatrixMode(GL_MODELVIEW);
    
    glutPostRedisplay();
}

//draw all bombs
void drawBombs(){
    list<Bomb*>::iterator bombit;
    for(bombit=bombs.begin();bombit!=bombs.end();bombit++){
        (*bombit)->paint();
    }
}

//display callback
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //draw all layers here, and the things are drawn by these layers
    layer[4].drawThings();
    layer[3].drawThings();
    layer[2].drawThings();
    layer[1].drawThings();
    layer[0].drawThings();
    
    drawBombs();
    
    glFlush();
    
    glutSwapBuffers();
}

//player drops a bomb on the current position
void dropBomb(int x,int y){
    Bomb *b = new Bomb(x,y,0);
    bombs.push_back(b);
}

//the game is paused
void pauseGame(){
    game_status= game_status==RUN ? PAUSE : RUN;
}

//mouse callback
void mouse(int button,int status,int x,int y){
    if(status==GLUT_UP){
        switch (button) {
            case GLUT_LEFT_BUTTON:
                dropBomb(x*400/width, y*400/height);
                break;
            case GLUT_MIDDLE_BUTTON:
                pauseGame();
                break;
            case GLUT_RIGHT_BUTTON:
                if(game_status==RUN){//when it's running, pause it.
                    pauseGame();
                }
                oneMovement();
                debugOutput();
                break;
            default:
                break;
        }
        glutPostRedisplay();
    }
}
//keyboard callback
void keyboard(unsigned char c, int x, int y){
    switch (c) {
        case 'q':
        case 'Q':
            quit();
            break;
        case 'p':
        case 'P':
            pauseGame();
            break;
        case 13://enter key
			if (FULLSCREEN) {//toggle between full screen and window mode
				glutReshapeWindow(400, 400);
				glutPositionWindow(400, 200);
				FULLSCREEN=false;
			}else {
				glutFullScreen();
				FULLSCREEN=true;
			}
			break;
        default:
            break;
    }
    glutPostRedisplay();
}

void oneMovement(){
    detectCollision();
    thingsMove();
    if(counter>=10000){//every 10 seconds, we have more new friends
        counter=0;
        thingSpawn();
    }
    counter+=INTERVAL;
}

//timer callback
void timerfunc(int status){
    if(status == RUN){
        oneMovement();
    }
    //debugOutput();
    glutTimerFunc(INTERVAL, timerfunc, game_status);
    glutPostRedisplay();
}

void thingsMove(){
    for (int i=0; i<LAYERNUM; i++) {
        //things move at every layer
        layer[i].thingsMovement();
    }

    list<Bomb*>::iterator it;
    for(it=bombs.begin(); it!=bombs.end(); it++){
        if((*it)->forwardToBottom()){
            //bomb reaches the bottom, eliminated
            bombs.erase(it);
        }
    }
    
}

void detectCollision(){
    list<Bomb*>::iterator it;
    for(it=bombs.begin(); it!=bombs.end(); it++){
        int kills = (*it)->hitLevel(&layer[(*it)->getLevel()]);
        if(kills > 0){
            
        }
    }
}

void thingSpawn(){
    //Engaging more bad things. Try to eliminate them all!
    layer[3].generateThings(BAD);
    layer[4].generateThings(BAD);
    
    //we have more good things. Thus making the game harder.
    layer[0].generateThings(GOOD);
    layer[1].generateThings(GOOD);
    layer[2].generateThings(GOOD);
}

void debugOutput(){
    //for debug purpose
    list<Bomb*>::iterator it;
    for(it=bombs.begin();it!=bombs.end();it++){
        (*it)->printInfo();
    }
    for (int i=0; i<LAYERNUM; i++) {
        layer[i].printInfo();
    }
    cout<<"one loop========"<< counter <<endl;

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
    glutTimerFunc(INTERVAL, timerfunc, PAUSE);
    
    customInit();
    
    glutMainLoop();
    
    return 0;
}

void quit(){
    bombs.clear();
    exit(0);
}