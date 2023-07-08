#include <iostream>
#include <fstream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "background.hpp"

void crashGame(std::string message);


void Background::setBg(std::string file, std::string name, float speed, int sizex, int sizey, u8 layer){
    bgFile = file;
    bgName = name;
    scrollSpeed = speed;
    sizeX = sizex;
    sizeY = sizey;
    bgLayer = layer;
    set = true;
}

void Background::loadBg(){
    if(!loaded && set){
        NF_LoadTiledBg(bgFile.data(), bgName.data(), sizeX, sizeY);
        loaded = true;
    }
}

void Background::unLoadBg(){
    if(loaded && set){
        NF_UnloadTiledBg(bgName.data());
        loaded = false;
    }
}

void Background::createBg(){
    if(!created && set){
        NF_CreateTiledBg(0, bgLayer, bgName.data());
        created = true;
    }
}

void Background::deleteBg(){
    if(created && set){
        NF_DeleteTiledBg(0, bgLayer);
        created = false;
    }
}

void Background::scrollBg(int positionX, int positionY){
    NF_ScrollBg(0, bgLayer, positionX, positionY);
}

Background::~Background(){
    if(!created) deleteBg();
    if(!loaded) unLoadBg();
}

LevelBackground::LevelBackground(std::string bgFilename){
    std::ifstream bgFile(bgFilename);
    std::string readText;
    std::getline(bgFile, readText);
    if(readText != "_BG"){
        NF_Error(229, "d", 3);
    }
    for(int i = 0; i < 4; i++){
        std::getline(bgFile, readText);
        readText.erase(0, 1);
        if(std::stoi(readText) != i) NF_Error(5, "ds", 2);
        std::getline(bgFile, readText);
        if(readText == "\\") continue;
        std::string tempName = readText;
        std::getline(bgFile, readText);
        float tempSpeed = std::stof(readText);
        std::getline(bgFile, readText);
        int tempSizeX = std::stoi(readText);
        std::getline(bgFile, readText);
        int tempSizeY = std::stoi(readText);
        bg[i].setBg(tempName, std::to_string(i), tempSpeed, tempSizeX, tempSizeY, (u8)i);
        created[i] = true;
    }
    std::getline(bgFile, readText);
    if(readText != ":C") NF_Error(5, "ds", 2);
    std::getline(bgFile, readText);
    colMapName = readText;
    std::getline(bgFile, readText);
    colMapSizeX = std::stoi(readText);
    std::getline(bgFile, readText);
    colMapSizeY = std::stoi(readText);
    bgFile.close();
}

void LevelBackground::loadBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg[i].loadBg();
        }
    }
    else{
        bg[id].loadBg();
    }
}

void LevelBackground::unLoadBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg[i].unLoadBg();
        }
    }
    else{
        bg[id].unLoadBg();
    }
}

void LevelBackground::createBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg[i].createBg();
        }
    }
    else{
        bg[id].createBg();
    }
}

void LevelBackground::deleteBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg[i].deleteBg();
        }
    }
    else{
        bg[id].deleteBg();
    }
}

void LevelBackground::scrollBg(uint id, int positionX, int positionY){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg[i].scrollBg(positionX, positionY);
        }
    }
    else{
        bg[id].scrollBg(positionX, positionY);
    }
}

void LevelBackground::loadCol(){
    NF_LoadColisionMap(colMapName.data(), 0, colMapSizeX, colMapSizeY);
    colMapActive = true;
}

void LevelBackground::unLoadCol(){
    NF_UnloadColisionMap(0);
    colMapActive = false;
}