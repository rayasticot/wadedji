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
#include "entities/genieboss.hpp"


GenieBoss::GenieBoss(int id, int sprite, int palette, int posx, int posy, int hp){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    initialHeight = positionY;
    initialX = positionX;
    idlePosY = initialHeight;
    speedX = 0;
    speedY = 0;
    sizeX = 64;
    sizeY = 64;
    health = hp;
    type = 2;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

void GenieBoss::idle(){
    float add = fixedToFloat(sinLerp(degreesToAngle(timer)), 12)*4;
    positionY = idlePosY+add;
    if(positionX < initialX){
        positionX += 2;
    }
    if(positionX > initialX){
        positionX -= 2;
    }
    if(health < 16){
        if((fullTimer % 120) == 1){
            proj = 3;
        }
    }
}

void GenieBoss::fall(){
    if(!checkRangeMapCollisionX(0, positionX, positionY+64, 8)){
        positionY += 2;
    }
    else{
        state = 2;
        direction = false;
        if(playerPosX < positionX){
            direction = true;
        }
    }
}

void GenieBoss::moveToPlayer(){
    if(direction){
        if(!checkRangeMapCollisionY(0, positionX-1, positionY, 8)){
            positionX -= 2;
        }
        else{
            state = 3;
        }
    }
    else{
        if(!checkRangeMapCollisionY(0, positionX+64, positionY, 8)){
            positionX += 2;
        }
        else{
            state = 3;
        }
    }
}

void GenieBoss::rise(){
    if(positionY > initialHeight){
        positionY -= 2;
    }
    else{
        fullTimer = 0;
        state = 0;
    }
}

void GenieBoss::update(){
    if(!alive){
        updateGravity();
        return;
    }
    if(hurtTime > 0){
        hurtTime--;
        blink = !blink;
    }
    timer += 15;
    timer %= 360;
    fullTimer += 1;
    proj = 0;
    switch(state){
        case -1:
            break;
        case 0:
            if(fullTimer == 459){
                state = 1;
            }
            idle();
            break;
        case 1:
            fall();
            break;
        case 2:
            moveToPlayer();
            break;
        case 3:
            rise();
            break;
    }
}

void GenieBoss::getPlayer(Player* player){
    playerPosX = player->getPosX();
}

int GenieBoss::getProj(){
    return proj;
}

GenieBoss::~GenieBoss(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}