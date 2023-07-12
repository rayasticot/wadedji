#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "ennemy.hpp"
#include "pig.hpp"

#define H_SPEED_LIMIT 1.5
#define H_ACC 0.1


Pig::Pig(int id, int sprite, int palette, int posx, int posy){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    speedX = 0;
    speedY = 0;
    sizeX = 16;
    sizeY = 32;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
}

void Pig::update(){
    if(checkRangeMapCollisionY(0, positionX+speedX+17, positionY, 4)){
        dirRight = false;
        speedX = 0;
    }
    else if(checkRangeMapCollisionY(0, positionX+speedX-1, positionY, 4)){
        dirRight = true;
        speedX = 0;
    }
    if(dirRight) accelerationX = H_ACC;
    else         accelerationX = -H_ACC;
    speedX += accelerationX;
    if(speedX > H_SPEED_LIMIT) speedX = H_SPEED_LIMIT;
    if(speedX < -H_SPEED_LIMIT) speedX = -H_SPEED_LIMIT;
    positionX += speedX;
}