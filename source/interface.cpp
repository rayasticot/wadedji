#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "interface.hpp"


void Interface::start(){
    NF_LoadTilesForBg("ui/bottomtilemap", "bottommap", 256, 256, 0, 11);
    NF_CreateTiledBg(1, 1, "bottommap");
}

void Interface::update(int health, int mana, int maxMana){
    for(int i = 0; i < 32; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 11);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 11);
    }
    for(int i = 0; i < health; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 1);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 2);
    }
    for(int i = 0; i < 10; i++){
        NF_SetTileOfMap(1, 1, 22+i, 0, 11);
    }
    if(mana > 0){
        int mana80 = ((float)mana/(float)maxMana)*80;
        int manaNumber = mana80/8;
        for(int i = 0; i < manaNumber; i++){
            NF_SetTileOfMap(1, 1, 31-i, 0, 3);
        }
        int manaFirst = mana80%8;
        if(manaFirst){
            NF_SetTileOfMap(1, 1, 31-manaNumber, 0, 11-manaFirst);
        }
    }
    NF_UpdateVramMap(1, 1);
}