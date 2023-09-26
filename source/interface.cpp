#include <iostream>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "interface.hpp"


void Interface::start(){
    NF_LoadTilesForBg("ui/bottomtilemap", "bottommap", 256, 256, 0, 11);
    NF_CreateTiledBg(1, 1, "bottommap");

    NF_LoadSpriteGfx("ui/spr/rond", 128, 64, 64);
    NF_VramSpriteGfx(1, 128, 0, false);
    NF_LoadSpritePal("ui/pal/rond", 16);
    NF_VramSpritePal(1, 16, 0);

    NF_CreateSprite(1, 0, 0, 0, 152, 0);
    NF_CreateSprite(1, 1, 0, 0, 192, 64);
    NF_CreateSprite(1, 2, 0, 0, 112, 64);
    NF_CreateSprite(1, 3, 0, 0, 152, 128);
    NF_SpriteFrame(1, 3, 1);
    NF_SpriteFrame(1, 2, 1);
    NF_CreateSprite(1, 4, 0, 0, 24, 128);
}

void Interface::drawHealth(int health){
    for(int i = 0; i < 32; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 11);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 11);
    }
    for(int i = 0; i < health; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 1);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 2);
    }
}

void Interface::drawMana(int mana, int maxMana){
    for(int i = 0; i < 10; i++){
        NF_SetTileOfMap(1, 1, 22+i, 0, 11);
    }
    if(mana > 0){
        int mana80 = ((float)mana/(float)maxMana)*80;
        int manaNumber = mana80/8;
        for(int i = 0; i < manaNumber; i++){
            NF_SetTileOfMap(1, 1, 9-i, 4, 3);
        }
        int manaFirst = mana80%8;
        if(manaFirst){
            NF_SetTileOfMap(1, 1, 9-manaNumber, 4, 11-manaFirst);
        }
    }
}

void Interface::update(int health, int mana, int maxMana){
    drawHealth(health);
    drawMana(mana, maxMana);
    NF_UpdateVramMap(1, 1);
}