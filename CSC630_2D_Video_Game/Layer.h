//
//  Layer.h
//  CSC630_2D_Video_Game
//
#ifndef LAYER_H
#define LAYER_H

#include <list>
#include "Thing.h"

using namespace std;

const int LAYERNUM = 5;

class Layer{
    
private:
    list<Thing> thingsCollection;
    
public:
    Layer(){};
    ~Layer(){};

    void generateThings(int type);
    void thingsMovement();
    void drawThings();
    void putThing(Thing *thing);
};
#endif