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
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "entities/basictrajproj.hpp"


BasicTrajProj::BasicTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    sizeX = 8;
    sizeY = 8;
    damage = projDamage;
    speedMul = projSpeed;
    speedX = targetX-positionX;
    speedY = targetY-positionY;
    normalizeSpeed();
    speedX *= speedMul;
    speedY *= speedMul;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

int BasicTrajProj::update(){
    positionX += speedX;
    positionY += speedY;
    if(NF_GetTile(0, positionX+(sizeX/2), positionY+(sizeX/2)) == 1){
        touch = 1;
    }
    return touch;
}

BasicTrajProj::~BasicTrajProj(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}