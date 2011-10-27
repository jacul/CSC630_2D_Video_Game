//
//  Thing.cpp
//  CSC630_2D_Video_Game
//
//

#ifndef THING_H
#define THING_H

#include <iostream>

using namespace std;

#define GOOD 0
#define BAD 1

const float THINGCOLORS[5][3] = {{1,1,0},//yellow
    {1,0.8431,0},//gold
    {1,0.27,0},//orange red
    {0.54,0.1686,0.886},//blue violet
    {0.5647,0,0.82745}};//dark violet

const int HALFSIZE = 5;//so the whole size is 10.
const float DR = 3.14159/180;

class Thing{
    
protected:
    int x, y, z;
    int r,spd;
    bool dead;
    int deadcounter;
    
public:
    Thing(int x, int y, int z);
    ~Thing(){};

    void paint();
    void move();
    virtual int getThingType()=0;
    int getX(){return x;};
    int getY(){return y;};
    void printInfo();
    void kill(){dead=true;};
    bool canRemove(){if(dead)deadcounter++;return dead &&deadcounter>=2;};
};

class BadThing:virtual public Thing{
    
public:
    BadThing(int x,int y,int z):Thing(x,y,z){};
    int getThingType();
};

class GoodThing:public Thing{
    
public:
    GoodThing(int x,int y,int z):Thing(x,y,z){};
    int getThingType();
};
#endif