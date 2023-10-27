#include <iostream>
#include <fstream>
#include <cmath>
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


int Ennemy::checkHit(Player* player){
    int pStartX = player->getPosX()+8;
    int pStartY = player->getPosY()+player->getCrouchPosY();
    int pSizeX = 16;
    int pSizeY = player->getSizeY();

    if(checkCollision(pStartX, pStartY, pSizeX, pSizeY)){
        if(player->getPound()){
            return 2;
        }
        if(player->getAttack() > 0){
            if(!player->getSide()){
                pStartX += pSizeX;
            }
            if(checkCollision(pStartX, pStartY, pSizeX/2, pSizeY)){
                return 2;
            }
        }
        if(health > 0){
            return 1;
        }
    }

    return 0;
}

void Ennemy::hurt(int damage, float direction){
    health -= damage;
    if(health < 0){
        health = 0;
    }
    speedX = direction*(damage*2.5);
    hurtTime = 20;
}