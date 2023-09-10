#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "basictrajproj.hpp"


BasicTrajProj::BasicTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    sizeX = 8;
    sizeY = 8;
    damage = projDamage;
    speed = projSpeed;
    dirX = targetX-positionX;
    dirY = targetY-positionY;
    normalizeDir();
    dirX *= speed;
    dirY *= speed;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

int BasicTrajProj::update(){
    positionX += dirX;
    positionY += dirY;
    if(NF_GetTile(0, positionX+(sizeX/2), positionY+(sizeX/2))){
        touch = 1;
    }
    return touch;
}

BasicTrajProj::~BasicTrajProj(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}