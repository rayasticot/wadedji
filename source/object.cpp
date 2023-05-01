#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"

#define SIZE_SCREEN_X 256
#define SIZE_SCREEN_Y 192


void Object::moveCamToPos(){
    bool flagNotCenterX = false;
    bool flagNotCenterY = false;
    int camPositionX = 0;
    int camPositionY = 0;
    
    const int positionScreenCenterX = (SIZE_SCREEN_X-sizeX)/2;
    const int positionScreenCenterY = (SIZE_SCREEN_Y-sizeY)/2;

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
    if(positionX > 768/**/-136){
        positionScreenX = positionX-(768/**/-256);
        flagNotCenterX = true;
    }
    if(positionY > 768/**//**/-112){
        positionScreenY = positionY-(768/**/-192);
        flagNotCenterY = true;
    }

    if(flagNotCenterX == false){
        camPositionX = positionX-positionScreenCenterX;
    }
    else{
        if(positionX < positionScreenCenterX){
            camPositionX = 0;
        }
        if(positionX > 768/**/-136){
            camPositionX = 768/**/-256;
        }
    }

    if(flagNotCenterY == false){
        camPositionY = positionY-positionScreenCenterY;
    }
    else{
        if(positionY < positionScreenCenterY){
            camPositionY = 0;
        }
        if(positionY > 768/**//**/-112){
            camPositionY = 768/**//**/-192;
        }
    }
    NF_ScrollBg(0, 0, camPositionX, camPositionY);
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