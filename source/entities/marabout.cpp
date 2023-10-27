#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>
#include <functional>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "entities/entity.hpp"
#include "item.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/ennemy.hpp"
#include "entities/marabout.hpp"

#define H_SPEED_LIMIT 1.5
#define H_ACC 0.1
#define H_DECELERATION 0.25
#define V_GRAVITYACC 0.15
#define V_SPEEDLIMIT 5


Marabout::Marabout(int id, int sprite, int palette, int posx, int posy, int hp, int projfind){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    speedX = 0;
    speedY = 0;
    offsetX = 8;
    sizeX = 16;
    sizeY = 32;
    health = hp;
    type = 1;
    projFind = projfind;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

void Marabout::updateAnimation(){
    if(speedX > 0){
        NF_HflipSprite(0, spriteId, true);
    }
    else if(speedX < 0){
        NF_HflipSprite(0, spriteId, false);
    }
    if(!alive){
        NF_SpriteFrame(0, spriteId, 2);
        return;
    }
    if(timeSinceProj > 80){
        NF_SpriteFrame(0, spriteId, 1);
        return;
    }
    NF_SpriteFrame(0, spriteId, 0);
}

void Marabout::update(){
    updateGravity();
    if(lastHealth != health){
        timeSinceProj = 90;
    }
    proj = 0;
    if(health > 0){
        if(timeSinceProj > 0){
            timeSinceProj--;
        }
        else{
            proj = projFind;
            timeSinceProj = 90;
        }
    }
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
    positionX += speedX;
    lastHealth = health;

    updateAnimation();
}

int Marabout::getProj(){
    return proj;
}

Marabout::~Marabout(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}