//
//  Layer.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Layer.h"

void Layer::generateThings(int type){
    if(type==GOOD){
        GoodThing *good = new GoodThing(40,40);
        putThing(good);
    }else if(type==BAD){
        BadThing *bad = new BadThing(10,10);
        putThing(bad);
    }
}

void Layer::thingsMovement(){
    list<Thing*>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        (*it)->paint();
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