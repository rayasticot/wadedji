#include <iostream>
#include <array>
#include <cmath>
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


void Projectile::kill(){
    touch = 1;
}

void Projectile::normalizeSpeed(){
    float norm = std::sqrt(std::pow(speedX, 2)+std::pow(speedY, 2));
    speedX /= norm;
    speedY /= norm;
}

int Projectile::checkHit(Player* player){
    int pStartX = player->getPosX()+8;
    int pStartY = player->getPosY()+player->getCrouchPosY();
    int pSizeX = 16;
    int pSizeY = player->getSizeY();

    if(checkCollision(pStartX, pStartY, pSizeX, pSizeY)){
        return 1;
    }

    return 0;
}

int Projectile::checkHit(Ennemy* ennemy){
    int pStartX = ennemy->getPosX();
    int pStartY = ennemy->getPosY();
    int pSizeX = ennemy->getSizeX();
    int pSizeY = ennemy->getSizeY();

    if(checkCollision(pStartX, pStartY, pSizeX, pSizeY)){
        return 1;
    }

    return 0;
}