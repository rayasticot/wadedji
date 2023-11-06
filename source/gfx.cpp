#include <iostream>
#include <vector>
#include <fstream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"

void crashGame(std::string message);

Sprite::Sprite(std::string fileName, u8 xSize, u8 ySize, u8 screen, u8 slot){
    nameSprite = fileName;
    sizeX = xSize;
    sizeY = ySize;
    screenNumber = screen;
    slotMemory = slot;
}

void Sprite::loadSpr(){
    if(loaded == false){
        NF_LoadSpriteGfx(nameSprite.data(), slotMemory, sizeX, sizeY);
        NF_VramSpriteGfx(screenNumber, slotMemory, slotMemory, false);
        loaded = true;
    }
}

void Sprite::unloadSpr(){
    //if(loaded == true){
        NF_UnloadSpriteGfx(slotMemory);
        NF_FreeSpriteGfx(screenNumber, slotMemory);
        loaded = false;
    //}
}

/*Sprite::~Sprite(){
    unloadSpr();
}*/

Palette::Palette(std::string fileName, u8 screen, u8 slot){
    namePalette = fileName;
    screenNumber = screen;
    slotMemory = slot;
}

void Palette::loadPal(){
    if(loaded == false){
        NF_LoadSpritePal(namePalette.data(), slotMemory);
        NF_VramSpritePal(screenNumber, slotMemory, slotMemory);
        loaded = true;
    }
}

void Palette::unloadPal(){
    //if(loaded == true){
        NF_UnloadSpritePal(slotMemory);
        loaded = false;
    //}
}

/*Palette::~Palette(){
    unloadPal();
}*/

void GfxGroup::readGfxFile(std::string fileName, u8 screen, int sprStart, int palStart){
    std::ifstream gfxFile(fileName);
    std::string readText;
    std::getline(gfxFile, readText);
    if(readText != "_GFX"){
        NF_Error(240, "d", 3);
    }
    std::getline(gfxFile, readText);
    std::getline(gfxFile, readText);
    if(readText != "_SPR"){
        NF_Error(241, "d", 3);
    }
    int sprIndex = sprStart;
    while(readText != "_PAL"){
        std::getline(gfxFile, readText);
        std::string tempSprName = readText;
        std::getline(gfxFile, readText);
        int tempSizeX = std::stoi(readText);
        std::getline(gfxFile, readText);
        int tempSizeY = std::stoi(readText);
        spriteVector.push_back(Sprite(tempSprName, (u8)tempSizeX, (u8)tempSizeY, screen, sprIndex));
        sprIndex++;
        std::getline(gfxFile, readText);
    }
    int palIndex = palStart;
    while(std::getline(gfxFile, readText)){
        paletteVector.push_back(Palette(readText, screen, palIndex));
        palIndex++;
    }
    gfxFile.close();
}
/*
GfxGroup::GfxGroup(std::string fileName, u8 screen, int sprStart, int palStart){
    std::ifstream gfxFile(fileName);
    std::string readText;
    std::getline(gfxFile, readText);
    if(readText != "_GFX"){
        NF_Error(229, "d", 3);
    }
    std::getline(gfxFile, readText);
    std::getline(gfxFile, readText);
    if(readText != "_SPR"){
        NF_Error(229, "d", 3);
    }
    int sprIndex = sprStart;
    while(readText != "_PAL"){
        std::getline(gfxFile, readText);
        std::string tempSprName = readText;
        std::getline(gfxFile, readText);
        int tempSizeX = std::stoi(readText);
        std::getline(gfxFile, readText);
        int tempSizeY = std::stoi(readText);
        spriteVector.push_back(Sprite(tempSprName, (u8)tempSizeX, (u8)tempSizeY, screen, sprIndex));
        sprIndex++;
        std::getline(gfxFile, readText);
    }
    int palIndex = palStart;
    while(std::getline(gfxFile, readText)){
        paletteVector.push_back(Palette(readText, screen, palIndex));
        palIndex++;
    }
    gfxFile.close();
}
*/
void GfxGroup::loadSpr(uint id){
    if(id >= 128){
        for(auto i : spriteVector){
            i.loadSpr();
        }
    }
    else{
        spriteVector.at(id).loadSpr();
    }
}

void GfxGroup::unloadSpr(uint id){
    if(id >= 128){
        for(auto i : spriteVector){
            i.unloadSpr();
        }
    }
    else{
        spriteVector.at(id).unloadSpr();
    }
}

void GfxGroup::loadPal(uint id){
    if(id >= 16){
        for(auto i : paletteVector){
            i.loadPal();
        }
    }
    else{
        paletteVector.at(id).loadPal();
    }
}

void GfxGroup::unloadPal(uint id){
    if(id >= 16){
        for(auto i : paletteVector){
            i.unloadPal();
        }
    }
    else{
        paletteVector.at(id).unloadPal();
    }
}