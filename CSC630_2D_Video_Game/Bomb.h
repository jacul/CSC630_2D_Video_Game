//
//  Bomb.h
//  CSC630_2D_Video_Game
//
//

#ifndef CSC630_2D_Video_Game_Bomb_h
#define CSC630_2D_Video_Game_Bomb_h

#include "Thing.h"
#include "Layer.h"

const float BOMBCOLORS[5][3] = {
    0, 1,   0,
    0, 0.8,0,
    0, 0.6  ,0,
    0, 0.4,0,
    0,0.3,0
};
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
