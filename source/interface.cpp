#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "interface.hpp"


void Interface::start(){
    NF_LoadSpriteGfx("ui/spr/lifebone", 128, 8, 16);
    NF_VramSpriteGfx(1, 128, 0, true);
    NF_LoadSpritePal("ui/pal/lifebone", 16);
    NF_VramSpritePal(1, 16, 0);

    for(int i = 0; i < 32; i++){
        NF_CreateSprite(1, i, 0, 0, 256, 192);
    }
}

void Interface::update(int health){
    for(int i = 0; i < 32; i++){
        NF_MoveSprite(1, i, 256, 192);
    }
    for(int i = 0; i < health; i++){
        NF_MoveSprite(1, i, 0 + (i%16)*8, 0 + (i/16)*16);
    }
}