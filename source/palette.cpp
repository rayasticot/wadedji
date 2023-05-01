#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfxhandler.hpp"
extern GfxHandler gfx;

GfxHandler::Palette::Palette(std::string fileName, u8 screen, u8 index){
    namePalette = fileName;
    screenNumber = screen;
    arrayIndex = index;
    slotMemory = -1;
}

void GfxHandler::Palette::loadInMemory(){
    bool checkMemorySpace = false;
    for(int i = 0; i < 16; i++){
        if(gfx.paletteMemoryMap[i] == -1){
            slotMemory = i;
            gfx.paletteMemoryMap[i] = arrayIndex;
            checkMemorySpace = true;
            break;
        }
    }
    if(checkMemorySpace == false) NF_Error(gfx.paletteMemoryMap[0], "A", 0);
    std::string fileNameToLoad = "pal/"+namePalette;
    NF_LoadSpritePal(fileNameToLoad.data(), slotMemory);
	NF_VramSpritePal(screenNumber, slotMemory, slotMemory);
}

void GfxHandler::Palette::unloadInMemory(){
    NF_UnloadSpritePal(slotMemory);
    gfx.paletteMemoryMap[slotMemory] = -1;
    slotMemory = -1;
}