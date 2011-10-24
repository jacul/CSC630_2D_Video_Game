//
//  Bomb.h
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef CSC630_2D_Video_Game_Bomb_h
#define CSC630_2D_Video_Game_Bomb_h

#include "Thing.h"
#include "Layer.h"

class Bomb{

private:
    int x,y,z;
    
public:
    Bomb(int x,int y,int z){this->x=x;this->y=y;this->z=z;};
    ~Bomb(){};
    
    bool isCollision(Thing *thing);
    bool forwardToBottom();
    void paint();
    int getLevel();
    int hitLevel(Layer *layer);
    
    void printInfo();
};
#endif
