#include <iostream>
#include <array>
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
#include "entities/projectile.hpp"
#include "entities/bloodproj.hpp"


BloodProj::BloodProj(int id, int sprite, int palette, int posx, int posy, int angle){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    sizeX = 8;
    sizeY = 8;
    speedX = (int)(fixedToFloat(cosLerp(degreesToAngle(angle)), 12)*10);
    speedY = (int)(fixedToFloat(sinLerp(degreesToAngle(angle)), 12)*10);

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

int BloodProj::update(){
    updateGravity();
    if(checkRangeMapCollisionY(0, positionX+speedX+8, positionY, 2)){
        speedX = -speedX;
    }
    else if(checkRangeMapCollisionY(0, positionX+speedX-1, positionY, 2)){
        speedX = -speedX;
    }
    if(checkRangeMapCollisionX(0, positionX, positionY+sizeY, 2)){
        NF_SpriteFrame(0, spriteId, 1);
    }
    positionX += speedX;
    if(speedY < 0){
        if(checkRangeMapCollisionX(0, positionX, positionY, 2)){ // Détecte plafond
            speedY = 0.1;
        }
        positionY += speedY;
    }

    return touch;
}

BloodProj::~BloodProj(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}