//
//  Layer.cpp
//  CSC630_2D_Video_Game
// This class defines the level of this game. Level holds all the things. It perform things' movement and collisions.
//

#include <iostream>
#include <stdlib.h>
#include "Layer.h"

void Layer::generateThings(int type){
    generateThings(type, 1);
}

void Layer::generateThings(int type, int num){
    for (int i=0; i<num; i++) {
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
}

void Layer::thingsMovement(){
    list<Thing*>::iterator it;
    for(it=thingsCollection.begin(); it!=thingsCollection.end(); it++){
        (*it)->move();
        if((*it)->canRemove())
        {
            it=thingsCollection.erase(it);
            it--;
            continue;
        }
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