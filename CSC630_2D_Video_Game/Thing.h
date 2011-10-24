//
//  Thing.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef THING_H
#define THING_H

#include <iostream>

using namespace std;

#define GOOD 0
#define BAD 1

class Thing{
    
protected:
    int x, y;
    
public:
    Thing(int x, int y){this->x=x;this->y=y;};
    ~Thing(){};

    void paint();
    void move();
    virtual int getThingType()=0;
    int getX(){return x;};
    int getY(){return y;};
    void printInfo();
};

class BadThing:virtual public Thing{
    
public:
    BadThing(int x,int y):Thing(x,y){};
    int getThingType();
};

class GoodThing:public Thing{
    
public:
    GoodThing(int x,int y):Thing(x,y){};
    int getThingType();
};
#endif