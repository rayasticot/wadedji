#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfxhandler.hpp"
extern GfxHandler gfx;

GfxHandler::Sprite::Sprite(std::string fileName, u8 xSize, u8 ySize, u8 screen, u8 index){
    nameSprite = fileName;
    sizeX = xSize;
    sizeY = ySize;
    screenNumber = screen;
    arrayIndex = index;
    slotMemory = -1;
}

void GfxHandler::Sprite::loadInMemory(){
    bool checkMemorySpace = false;
    for(int i = 0; i < 128; i++){
        if(gfx.spriteMemoryMap[i] == -1){
            slotMemory = i;
            gfx.spriteMemoryMap[i] = arrayIndex;
            checkMemorySpace = true;
            break;
        }
    }
    if(checkMemorySpace == false) NF_Error(229, "A", 0);
    std::string fileNameToLoad = "spr/"+nameSprite;
    NF_LoadSpriteGfx(fileNameToLoad.data(), slotMemory, sizeX, sizeY);
	NF_VramSpriteGfx(screenNumber, slotMemory, slotMemory, true);
}

void GfxHandler::Sprite::unloadInMemory(){
    NF_UnloadSpriteGfx(slotMemory);
    NF_FreeSpriteGfx(screenNumber, slotMemory);
    gfx.spriteMemoryMap[slotMemory] = -1;
    slotMemory = -1;
}