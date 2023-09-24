#include <iostream>
#include <cmath>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "entities/entity.hpp"

#define SIZE_SCREEN_X 256
#define SIZE_SCREEN_Y 192

#define V_GRAVITYACC 0.15
#define V_SPEEDLIMIT 5

void Entity::moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY){
    /*
    const int positionScreenCenterX = (SIZE_SCREEN_X-sizeX)/2;
    const int positionScreenCenterY = (SIZE_SCREEN_Y-sizeY)/2;

    flagNotCenterX = false;
    flagNotCenterY = false;

    positionScreenX = positionScreenCenterX;
    positionScreenY = positionScreenCenterY;

    if(positionX < positionScreenCenterX){
        positionScreenX = positionX;
        flagNotCenterX = true;
    }
    if(positionY < positionScreenCenterY){
        positionScreenY = positionY;
        flagNotCenterY = true;
    }
    if(positionX > screenSizeX-136){
        positionScreenX = positionX-(screenSizeX-256);
        flagNotCenterX = true;
    }
    if(positionY > screenSizeY-112){
        positionScreenY = positionY-(screenSizeY-192);
        flagNotCenterY = true;
    }
    */
    
    positionScreenX = positionX-camPositionX;
    positionScreenY = positionY-camPositionY;

    if(positionScreenX < -64 || positionScreenX > SIZE_SCREEN_X){
        positionScreenX = SIZE_SCREEN_X;
    }

    if(positionScreenY < -64 || positionScreenY > SIZE_SCREEN_Y){
        positionScreenY = SIZE_SCREEN_Y;
    }
}

void Entity::moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY, int sizeXModif, int sizeYModif){
    const int positionScreenCenterX = (SIZE_SCREEN_X-(sizeX+sizeXModif))/2;
    const int positionScreenCenterY = (SIZE_SCREEN_Y-(sizeY+sizeYModif))/2;

    flagNotCenterX = false;
    flagNotCenterY = false;

    if(positionX < positionScreenCenterX){
        flagNotCenterX = true;
    }

    if(positionY < positionScreenCenterY){
        flagNotCenterY = true;
    }

    if(positionX > screenSizeX-136){
        flagNotCenterX = true;
    }

    if(positionY > screenSizeY-112){
        flagNotCenterY = true;
    }
 
    if(!flagNotCenterX){
        *camPositionX = positionX-positionScreenCenterX+shakeX;
    }
    else{
        if(positionX < positionScreenCenterX){
            *camPositionX = 0;
        }
        if(positionX > screenSizeX-136){
            *camPositionX = screenSizeX-256;
        }
    }

    if(!flagNotCenterY){
        *camPositionY = positionY-positionScreenCenterY+shakeY;
    }
    else{
        if(positionY < positionScreenCenterY){
            *camPositionY = 0;
        }
        if(positionY > screenSizeY-112){
            *camPositionY = screenSizeY-192;
        }
    }

    if(shakeX > 0){ shakeX--; }
    if(shakeX < 0){ shakeX++; }
    if(shakeY > 0){ shakeY--; }
    if(shakeY < 0){ shakeY++; }
}

bool Entity::checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange){
    if(pixelRange > 8) NF_Error(229, "NTM", 0);
    for(int i = 0; i < pixelRange*4; i++){
        if(NF_GetTile(collisionMapSlot, startX+(2*i), startY) == 1) return true;
    }
    return false;
}

bool Entity::checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange){
    if(pixelRange > 8) NF_Error(229, "NTM", 0);
    for(int i = 0; i < pixelRange*4; i++){
        if(NF_GetTile(collisionMapSlot, startX, startY+(2*i)) == 1) return true;
    }
    return false;
}

bool Entity::checkCollision(int posX, int posY, int otherSizeX, int otherSizeY){
    if((int)positionX+sizeX >= posX && (int)positionX < posX+otherSizeX){
        if((int)positionY+sizeY >= posY && (int)positionY < posY+otherSizeY){
            return true;
        }
    }
    return false;
}

void Entity::updateGravity(){
    if(checkRangeMapCollisionX(0, positionX, positionY+sizeY, 2) == false){
        if(speedY < 0) speedY += 0.5;
        accelerationY = V_GRAVITYACC;
        speedY += accelerationY;
        if(speedY > V_SPEEDLIMIT) speedY = V_SPEEDLIMIT;
    }
    else{
        accelerationY = 0;
        speedY = 0;
    }
    if(speedY > 0){
        for(int i = 0; i <= (int)speedY; i++){
            if(checkRangeMapCollisionX(0, positionX, positionY+sizeY+i, 2) == false) positionY++;
            else break;
        }
        positionY += (speedY - (int)speedY);
    }
}

void Entity::updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY){
    moveScreenPos(camPositionX, camPositionY, screenSizeX, screenSizeY);
    NF_MoveSprite(0, spriteId, positionScreenX, positionScreenY);
    if(blink){
        NF_MoveSprite(0, spriteId, 256, 192);
    }
}

void Entity::playSoundRandomPitch(mm_word sound){
    mm_sfxhand soundEffect = mmEffect(sound);
    int rate = 1024 * std::pow(2, ((rand()%9)-4)/24.0);
    mmEffectRate(soundEffect, rate);
}