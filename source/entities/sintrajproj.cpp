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
#include "entities/ennemy.hpp"
#include "entities/projectile.hpp"
#include "entities/sintrajproj.hpp"


SinTrajProj::SinTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage, int ampli, int cyc){
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
    s16 speedAngle = acosLerp(floatToFixed(speedX/1, 12));
    speedAngle += degreesToAngle(90);
    sideX = fixedToFloat(cosLerp(speedAngle), 12);
    sideY = fixedToFloat(sinLerp(speedAngle), 12);
    speedX *= speedMul;
    speedY *= speedMul;
    amplitude = ampli;
    cycle = cyc;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

int SinTrajProj::update(){
    timer += cycle;
    timer %= 360;
    float add = fixedToFloat(sinLerp(degreesToAngle(timer)), 12)*amplitude;
    float addX = sideX * add;
    float addY = sideY * add;
    positionX += speedX+addX;
    positionY += speedY+addY;
    if(NF_GetTile(0, positionX+(sizeX/2), positionY+(sizeX/2)) == 1){
        touch = 1;
    }
    return touch;
}

SinTrajProj::~SinTrajProj(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}