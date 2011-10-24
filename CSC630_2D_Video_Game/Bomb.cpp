//
//  Bomb.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-22.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#include "Bomb.h"
#include <iostream>

bool Bomb::isCollision(Thing *thing){
    int tx=thing->getX();
    int ty=thing->getY();
    return tx>=x-3 && tx<=x+3 && ty>=y-3 && ty<=y+3;
}

void Bomb::paint(){
    
}

void Bomb::printInfo(){
    cout<<"Bomb at: "<<x<<" "<<y<<" "<<z<<endl;
}

bool Bomb::forwardToBottom(){
    z++;
    return z>=LAYERNUM;
}

int Bomb::getLevel(){
    return z;
}

int Bomb::hitLevel(Layer *layer){
    int kills = 0;
    list<Thing*> *things = layer->getAllThings();
    list<Thing*>::iterator it;
    for(it=things->begin(); it!=things->end(); it++){
        if (isCollision(*it)) {
            things->erase(it);
            kills++;
        }
    }
    return kills;
}