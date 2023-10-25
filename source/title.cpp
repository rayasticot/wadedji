#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "title.hpp"

void fadeIn();
void fadeOut();


void Title::update(){
    while(1){
        scanKeys();
        NF_SpriteOamSet(0);
	    NF_SpriteOamSet(1);
	    swiWaitForVBlank();
	    oamUpdate(&oamMain);
	    oamUpdate(&oamSub);

        NF_SpriteFrame(0, 0, frame/4);
        NF_SpriteFrame(0, 1, frame/4);

        frame++;
        frame %= 20;
        if(KEY_START & keysDown()){
            break;
        }
    }
}

void Title::end(){
    fadeOut();
    mmStop();
    mmUnload(MOD_PASGENIAL);
    NF_DeleteTiledBg(0, 0);
    NF_UnloadTiledBg("title");
    NF_DeleteSprite(0, 0);
    NF_DeleteSprite(0, 1);
    NF_UnloadSpriteGfx(0);
    NF_FreeSpriteGfx(0, 0);
    NF_UnloadSpriteGfx(1);
    NF_FreeSpriteGfx(0, 1);
    NF_UnloadSpritePal(0);
}

Title::Title(){
    mmLoad(MOD_PASGENIAL);
    mmStart(MOD_PASGENIAL, MM_PLAY_LOOP);
    setBrightness(3, -16);
    NF_LoadTiledBg("menu/title", "title", 256, 256);
    NF_CreateTiledBg(0, 0, "title");
    NF_LoadSpriteGfx("menu/start0", 0, 64, 64);
    NF_VramSpriteGfx(0, 0, 0, false);
    NF_LoadSpriteGfx("menu/start1", 1, 64, 64);
    NF_VramSpriteGfx(0, 1, 1, false);
    NF_LoadSpritePal("menu/start", 0);
    NF_VramSpritePal(0, 0, 0);
    NF_CreateSprite(0, 0, 0, 0, 64, 128);
    NF_CreateSprite(0, 1, 1, 0, 128, 128);
    fadeIn();
    update();
    end();
}