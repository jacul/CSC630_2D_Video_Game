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

class Thing{
    
protected:
    int _x, _y, _z;
    
    
public:
    Thing(int x, int y, int z){_x=x;_y=y;_z=z;};
    ~Thing(){};
    void print();
    void paint();
    void move();
    int getX(){return _x;};
    int getY(){return _y;};
    int getZ(){return _z;};
};

class BadThing:public Thing{
    
public:
    BadThing(int x,int y, int z):Thing(x,y,z){};
    
};

class GoodThing:public Thing{
    
public:
    GoodThing(int x,int y, int z):Thing(x,y,z){};
    
};
#endif