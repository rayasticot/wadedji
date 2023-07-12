#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"

#define SIZE_SCREEN_X 256
#define SIZE_SCREEN_Y 192

void Object::moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY){
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

    if(positionScreenX < -64){
        positionScreenX = SIZE_SCREEN_X;
    }

    if(positionScreenY < -64){
        positionScreenY = SIZE_SCREEN_Y;
    }
}

void Object::moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY){
    const int positionScreenCenterX = (SIZE_SCREEN_X-sizeX)/2;
    const int positionScreenCenterY = (SIZE_SCREEN_Y-sizeY)/2;

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

bool Object::checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange){
    if(pixelRange > 8) NF_Error(229, "NTM", 0);
    for(int i = 0; i < pixelRange*4; i++){
        if(NF_GetTile(collisionMapSlot, startX+(2*i), startY) == 1) return true;
    }
    return false;
}

bool Object::checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange){
    if(pixelRange > 8) NF_Error(229, "NTM", 0);
    for(int i = 0; i < pixelRange*4; i++){
        if(NF_GetTile(collisionMapSlot, startX, startY+(2*i)) == 1) return true;
    }
    return false;
}

void Object::updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY){
    moveScreenPos(camPositionX, camPositionY, screenSizeX, screenSizeY);
    NF_MoveSprite(0, spriteId, positionScreenX, positionScreenY);
}