//
//  main.cpp
//  CSC630_2D_Video_Game
//  
// The goal of this game is to eliminate all the evil things and kill as few good things as you can.
//So, drop a bomb on these moving things by clicking your left mouse button. 
//Press middle mouse button to start/ resume and pause game. Right click to enter debug mode.
//By killing one bad thing, you gain scores. Killing good things will make you lose scores. 
//If you kill all the bad things, you win. If you kill so many good things that makes your score negative, you lose. 
//Also, dropping bombs consumes score. If you drop many bombs but gain no score, you might lose since your score is negative.
//Every 15 seconds, there will be more good things and bad things. So move fast before it's getting too crowded.
//
//  extra features:
//  startup message
//  fullscreen mode
//  more things appear after a fixed time
//  
//

#include "Thing.h"
#include "Layer.h"
#include "Bomb.h"

#include <string>
#include <stdlib.h>			// standard definitions
#include <stdio.h>			// C I/O (for sprintf) 
#include <math.h>
#include <list>
using namespace std;

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
#define END   2
#define WIN 3

#define INTERVAL 100

const char welcome[] = "Press MIDDLE button to start/resume!";
const char over[] = "Game Over!";
const char success[] = "You win!";
int game_status;
int width = 600;
int height = 600;

//five layers
Layer layer[LAYERNUM]={Layer(0),Layer(1),Layer(2),Layer(3),Layer(4)};
list <Bomb*> bombs;

int score;
int counter;

void *font = GLUT_BITMAP_9_BY_15;
bool FULLSCREEN=false;

//every fixed time, new things appear
void thingSpawn(int number);
//movement of the things
void thingsMove();
//check if the bomb hit the things
void detectCollision();
void quit();
void debugOutput();
//this function makes the game go one step further
void oneMovement();
void drawText(const char string[],int x,int y);
void drawPauseScreen();
void drawStatus();
void changeScore(int change);
void drawGameOver();
void drawSuccess();

void initGameObject(){
    //every level we have four things at the beginning
    thingSpawn(4);
}

void customInit(){
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    
    game_status=PAUSE;
    counter=0;
    score=500;//So you have 5 bombs at the beginning
    
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
    
    if(game_status==PAUSE)
        drawPauseScreen();
    else if(game_status==END)
        drawGameOver();
    else if(game_status==WIN)
        drawSuccess();
    drawStatus();
    
    glFlush();
    
    glutSwapBuffers();
}

//player drops a bomb on the current position
void dropBomb(int x,int y){
    changeScore(-100);//each bomb costs you 100, use them wisely!
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
                if(game_status==RUN)
                    dropBomb(x*400/width, y*400/height);
                break;
            case GLUT_MIDDLE_BUTTON:
                if(game_status==END||game_status==WIN){
                    score=500;
                }
                pauseGame();
                break;
            case GLUT_RIGHT_BUTTON:
                if(game_status==RUN){//when it's running, pause it.
                    pauseGame();
                }else
                if(game_status==PAUSE){
                    oneMovement();
                }
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
				glutReshapeWindow(600, 600);
				glutPositionWindow(400, 100);
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
    if(counter>=10000){//every 15 seconds, we have more new friends
        counter=0;
        thingSpawn(1);
    }
    counter+=INTERVAL;
}

//timer callback
void timerfunc(int status){
    if(status == RUN){
        oneMovement();
    }
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

void drawStatus(){
    char score_str[20];
    sprintf(score_str, "score: %i",score);
    drawText(score_str, 10, 10);
}

//draw text at the provided position.
void drawText(const char string[], int x, int y){
    glPushMatrix();
    
    int len = (int) strlen(string);
    
    glColor3f(1,1,1);
    glRasterPos2f(x, y);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
    glPopMatrix();
}

void drawCenter(const char string[]){
    int len = strlen(string);
    unsigned char *ss=new unsigned char[len];
    for (int i=0; i<len; i++) {
        ss[i]=string[i];
    }
    int stringwidth=glutBitmapLength(font, ss);
    
    int x=(width-stringwidth)*400/width/2;
    int y=200;
    drawText(string, x,y);
}

void drawGameOver(){
    drawCenter(over);
}

void drawSuccess(){
    drawCenter(success);
}

void drawPauseScreen(){
    drawCenter(welcome);
}

void changeScore(int change){
    score+=change;
    if (score<0) {
        game_status=END;
    }
}

void detectCollision(){
    list<Bomb*>::iterator it;
    for(it=bombs.begin(); it!=bombs.end(); it++){
        int kills = (*it)->hitLevel(&layer[(*it)->getLevel()]);
        changeScore(kills);
    }
    if(layer[3].getThingsNum()==0&&layer[4].getThingsNum()==0){
        //no more bad guys! you win!
        game_status=WIN;
    }
}
//parameters: numbers means how many things each level will have.
void thingSpawn(int number){
    //Engaging more bad things. Try to eliminate them all!
    layer[3].generateThings(BAD, number);
    layer[4].generateThings(BAD, number);
    
    //we have more good things. Thus making the game harder.
    layer[0].generateThings(GOOD, number);
    layer[1].generateThings(GOOD, number);
    layer[2].generateThings(GOOD, number);
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
    glutInitWindowPosition(400, 100);
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