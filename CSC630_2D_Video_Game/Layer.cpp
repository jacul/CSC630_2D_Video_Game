//
//  Layer.cpp
//  CSC630_2D_Video_Game
//
//  Created by zhu xiangdong on 11-10-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Layer.h"

void Layer::generateThings(){
    
}

void Layer::thingsMovement(){
    list<Thing>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        it->move();
    }
}

void Layer::drawThings(){
    
}

void Layer::putThing(Thing *thing){
    thingsCollection.push_back(*thing);
}