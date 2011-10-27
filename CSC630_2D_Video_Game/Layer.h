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
const int score_table[] = {-5000,-4000,-3000,3000,4000};
class Layer{
    
private:
    list<Thing*> thingsCollection;
    int z;
public:
    Layer(int z){this->z=z;};
    ~Layer(){thingsCollection.clear();};

    int getThingsNum(){return thingsCollection.size();};
    void generateThings(int type);
    void generateThings(int type, int num);
    void thingsMovement();
    void drawThings();
    void putThing(Thing *thing);
    int getLevelScore(){return score_table[z];};
    list<Thing*>* getAllThings();
    
    void printInfo();
};
#endif