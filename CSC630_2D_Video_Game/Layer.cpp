//
//  Layer.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "Layer.h"

void Layer::generateThings(int type){
    generateThings(type, 1);
}

void Layer::generateThings(int type, int num){
    if(type==GOOD){
        int x= rand()%398 +1;
        int y= rand()%398 +1;
        GoodThing *good = new GoodThing(x,y,z);
        putThing(good);
    }else if(type==BAD){
        int x= rand()%398 +1;
        int y= rand()%398 +1;
        BadThing *bad = new BadThing(x,y,z);
        putThing(bad);
    }
}

void Layer::thingsMovement(){
    list<Thing*>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        (*it)->move();
    }
}

void Layer::drawThings(){
    list<Thing*>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        (*it)->paint();
    }
}

void Layer::putThing(Thing *thing){
    thingsCollection.push_back(thing);
}

list<Thing *>* Layer::getAllThings(){
    return &thingsCollection;
}

void Layer::printInfo(){
    list<Thing*>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        (*it)->printInfo();
    }
}