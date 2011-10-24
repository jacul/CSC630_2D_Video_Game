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
    int _x, _y;
    int type;
    
public:
    Thing(int x, int y){_x=x;_y=y;type=-1;};
    ~Thing(){};

    void paint();
    void move();
    int getThingType(){return type;};
    int getX(){return _x;};
    int getY(){return _y;};
};

class BadThing:virtual public Thing{
    
public:
    BadThing(int x,int y):Thing(x,y){type=BAD;};
    
};

class GoodThing:public Thing{
    
public:
    GoodThing(int x,int y):Thing(x,y){type=GOOD;};
    
};
#endif