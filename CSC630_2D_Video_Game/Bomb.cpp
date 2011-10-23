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
    return (thing->getX()==x) && (thing->getY()==y);
}

void Bomb::paint(){
    
}