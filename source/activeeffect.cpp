#include <iostream>
#include <fstream>
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
#include "interface.hpp"
#include "entities/player.hpp"


void ActiveEffect::portefeuilleMagique(Player& player){
    if(!(player.timer % 60)){
        player.fcfa += 10;
    }
}

void ActiveEffect::attackGravity(Player& player){
    if(player.attackTime){
        player.parameters.vGravityAcc = 0;
        player.speedY = 0;
    }
    else{
        player.parameters.vGravityAcc = player.parameters.default_vGravityAcc;
    }
}

void ActiveEffect::applyActive(Player& player){
    for(auto& i : player.activeIndex){
        activeEffectList.at(i)(*this, player);
    }
}