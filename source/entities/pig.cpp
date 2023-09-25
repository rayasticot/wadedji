#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <functional>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "entities/entity.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/ennemy.hpp"
#include "entities/pig.hpp"

#define H_SPEED_LIMIT 1.5
#define H_ACC 0.1
#define H_DECELERATION 0.25
#define V_GRAVITYACC 0.15
#define V_SPEEDLIMIT 5


Pig::Pig(int id, int sprite, int palette, int posx, int posy, int hp){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    speedX = 0;
    speedY = 0;
    sizeX = 16;
    sizeY = 32;
    health = hp;
    type = 0;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

void Pig::update(){
    updateGravity();
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

int Pig::getProj(){
    return 0;
}

Pig::~Pig(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}