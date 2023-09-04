#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "player.hpp"
#include "ennemy.hpp"
#include "pig.hpp"

#define H_SPEED_LIMIT 1.5
#define H_ACC 0.1
#define H_DECELERATION 0.25


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
    if(hurtTime > 0){
        hurtTime--;
        blink = !blink;
    }
    else{
        blink = false;
    }
    if(health <= 0){
        blink = false;
    }
    if(health > 0 && hurtTime == 0){
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
    }
    else{
        if(speedX > H_DECELERATION) speedX -= H_DECELERATION;
        else if(speedX < -H_DECELERATION) speedX += H_DECELERATION;
        else speedX = 0;
        accelerationX = 0;

        if(checkRangeMapCollisionY(0, positionX+speedX+17, positionY, 4)){
            speedX = -speedX;
        }
        else if(checkRangeMapCollisionY(0, positionX+speedX-1, positionY, 4)){
            speedX = -speedX;
        }
    }
    positionX += speedX;
}