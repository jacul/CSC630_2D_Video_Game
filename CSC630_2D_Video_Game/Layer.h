//
//  Layer.h
//  CSC630_2D_Video_Game
//
#ifndef LAYER_H
#define LAYER_H

#include "Thing.h"
#include <list>

using namespace std;

const int LAYERNUM = 5;

class Layer{
    
private:
    list<Thing*> thingsCollection;
    
public:
    Layer(){};
    ~Layer(){thingsCollection.clear();};

    void generateThings(int type);
    void generateThings(int type, int num);
    void thingsMovement();
    void drawThings();
    void putThing(Thing *thing);
    list<Thing*>* getAllThings();
    
    void printInfo();
};
#endif