#include <iostream>
#include <array>
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
#include "entities/wadedji.hpp"
#include "entities/grounditem.hpp"


void GroundItem::update(){
    updateGravity();
    if(spawnWait > 0){
        spawnWait--;
        blink = !blink;
        if(!spawnWait){
            blink = false;
        }
    }
}

int GroundItem::checkHit(Player* player){
    int pStartX = player->getPosX()+8;
    int pStartY = player->getPosY();
    int pSizeX = 16;
    int pSizeY = 32;

    if(checkCollision(pStartX, pStartY, pSizeX, pSizeY)){
        return 1;
    }

    return 0;
}

GroundItem::GroundItem(int id, int sprite_, int palette_, int posx, int posy, int itemid){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    speedY = 0;
    sizeX = 16;
    sizeY = 16;
    itemId = itemid;
    NF_CreateSprite(0, spriteId, sprite_, palette_, positionScreenX, positionScreenY);
    NF_SpriteFrame(0, spriteId, itemId-1);
    nocashMessage(std::to_string(spriteId).data());
    spriteCreated = true;
}

GroundItem::~GroundItem(){
    if(spriteCreated){
        NF_DeleteSprite(0, spriteId);
    }
}