#include <iostream>
#include <cmath>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "projectile.hpp"


void Projectile::kill(){
    touch = 1;
}

void Projectile::normalizeDir(){
    float norm = std::sqrt(std::pow(dirX, 2)+std::pow(dirY, 2));
    dirX /= norm;
    dirY /= norm;
}

int Projectile::checkHit(Player* player){
    int pStartX = player->getPosX()+8;
    int pStartY = player->getPosY();
    int pSizeX = 16;
    int pSizeY = 32;

    if(checkCollision(pStartX, pStartY, pSizeX, pSizeY)){
        return 1;
    }

    return 0;
}