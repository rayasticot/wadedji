#include <iostream>
#include <fstream>
#include <array>
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
    int newPositionX = positionX;
    int newPositionY = positionY;
    if(bgLayer > 0){
        newPositionX = (int)positionX*0.5;
        newPositionY = (int)positionY*0.5;
    }
    NF_ScrollBg(0, bgLayer, newPositionX, newPositionY);
}

Background::~Background(){
    if(created) deleteBg();
    if(loaded) unLoadBg();
}

void LevelBackground::readBackgroundFile(std::string bgFilename){
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
        float tempSpeed = std::stof(readText); // Problème ici ça lit 0 alors que ça devrait lire 0.5 jsp pk
        std::getline(bgFile, readText);
        int tempSizeX = std::stoi(readText);
        std::getline(bgFile, readText);
        int tempSizeY = std::stoi(readText);
        bg.at(i).setBg(tempName, std::to_string(i), tempSpeed, tempSizeX, tempSizeY, (u8)i);
        created.at(i) = true;
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
            bg.at(i).loadBg();
        }
    }
    else{
        bg.at(id).loadBg();
    }
}

void LevelBackground::unLoadBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg.at(i).unLoadBg();
        }
    }
    else{
        bg.at(id).unLoadBg();
    }
}

void LevelBackground::createBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg.at(i).createBg();
        }
    }
    else{
        bg.at(id).createBg();
    }
}

void LevelBackground::deleteBg(uint id){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg.at(i).deleteBg();
        }
    }
    else{
        bg.at(id).deleteBg();
    }
}

void LevelBackground::scrollBg(uint id, int positionX, int positionY){
    if(id >= 4){
        for(int i = 0; i < 4; i++){
            bg.at(i).scrollBg(positionX, positionY);
        }
    }
    else{
        bg.at(id).scrollBg(positionX, positionY);
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

LevelBackground::~LevelBackground(){
    if(colMapActive) unLoadCol();
}