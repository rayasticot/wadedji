#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "title.hpp"

#include "fileconstants.hpp"

void fadeIn();
void fadeOut();


void Title::update(){
    scanKeys();
    NF_SpriteOamSet(0);
    NF_SpriteOamSet(1);
    swiWaitForVBlank();
    oamUpdate(&oamMain);
    oamUpdate(&oamSub);

    if(!action){
        NF_SpriteFrame(1, 0, frame/4);
        NF_SpriteFrame(1, 1, frame/4);
    }

    frame++;
    frame %= 20;
}

void Title::end(){
    fadeOut();
    mmStop();
    mmUnload(MOD_PASGENIAL);
    NF_DeleteSprite(1, 2);
    NF_DeleteTiledBg(0, 0);
    NF_UnloadTiledBg("title");
    //NF_DeleteSprite(0, 0);
    //NF_DeleteSprite(0, 1);
    NF_UnloadSpriteGfx(0);
    NF_FreeSpriteGfx(1, 0);
    NF_UnloadSpriteGfx(1);
    NF_FreeSpriteGfx(1, 1);
    NF_UnloadSpritePal(0);
    NF_UnloadSpriteGfx(2);
    NF_FreeSpriteGfx(1, 2);
    NF_UnloadSpritePal(1);
    NF_UnloadTextFont("font");
    NF_DeleteTextLayer(1, 0);
}

void Title::loadSprites(){
    NF_LoadTiledBg("menu/title", "title", 256, 256);
    NF_CreateTiledBg(0, 0, "title");
    NF_LoadSpriteGfx("menu/start0", 0, 64, 64);
    NF_VramSpriteGfx(1, 0, 0, false);
    NF_LoadSpriteGfx("menu/start1", 1, 64, 64);
    NF_VramSpriteGfx(1, 1, 1, false);
    NF_LoadSpritePal("menu/start", 0);
    NF_VramSpritePal(1, 0, 0);
    NF_LoadSpriteGfx("menu/skull_ui", 2, 16, 16);
    NF_VramSpriteGfx(1, 2, 2, false);
    NF_LoadSpritePal("menu/skull_ui", 1);
    NF_VramSpritePal(1, 1, 1);
}

void Title::loadProfileInfo(){
    for(int i = 0; i < 3; i++){
        std::ifstream read(saveFilePath+"wade"+std::to_string(i)+".sav");
        std::string readText;
        std::getline(read, readText);
        if(readText != "_SAV"){
            NF_Error(4000, "asd", 3);
        }
        std::getline(read, readText);
        started.at(i) = stoi(readText);
        std::getline(read, readText);
        std::getline(read, readText);
        alive.at(i) = stoi(readText);
        std::getline(read, readText);
        level.at(i) = stoi(readText);
        read.close();
    }
}

int Title::startScreen(bool fade){
    NF_ShowSprite(1, 2, false);
    NF_CreateSprite(1, 0, 0, 0, 64, 64);
    NF_CreateSprite(1, 1, 1, 0, 128, 64);
    if(fade){
        fadeIn();
    }
    while(!(KEY_START & keysDown()) && !(KEY_A & keysDown())){
        update();
    }

    NF_DeleteSprite(1, 0);
    NF_DeleteSprite(1, 1);
    NF_ShowSprite(1, 2, true);
    
    return 1;
}

int Title::profileScreen(){
    NF_WriteText16(1, 0, 8, 2, "Choisis un profil");
    for(int i = 0; i < 3; i++){
        if(started.at(i) == 1){
            std::string profilName = "WADEDJI"+std::to_string(i+1);
            NF_WriteText16(1, 0, 12, 4+(i*2), profilName.data());
        }
        else{
            NF_WriteText16(1, 0, 12, 4+(i*2), "NOUVEAU!");
        }
    }
    cursor = 0;
    int retourne = 2;
    while(1){
        NF_MoveSprite(1, 2, cursorPositionsX.at(cursor), cursorPositionsY.at(cursor));
        update();
        if(KEY_UP & keysDown()){
            cursor -= 1;
            if(cursor == -1){
                cursor = 2;
            }
        }
        if(KEY_DOWN & keysDown()){
            cursor += 1;
        }
        cursor %= 3;
        if(KEY_A & keysDown()){
            profile = cursor;
            break;
        }
        if(KEY_B & keysDown()){
            retourne = 0;
            break;
        }
        NF_UpdateTextLayers();
    }
    NF_ClearTextLayer16(1, 0);
    NF_UpdateTextLayers();

    return retourne;
}

int Title::menuScreen(){
    if(alive.at(profile) == 1){
        std::string continueText = "Reprendre (niveau "+std::to_string(level.at(profile))+")";
        NF_WriteText16(1, 0, 6, 2, continueText.data());
    }
    NF_WriteText16(1, 0, 11, 4, "Commencer!");
    cursor = 1;
    if(alive.at(profile) == 1){
        cursor = 0;
    }
    int retourne = 3;
    while(1){
        NF_MoveSprite(1, 2, cursorPositionsX.at(cursor+3), cursorPositionsY.at(cursor+3));
        update();
        if(KEY_UP & keysDown()){
            cursor += 1;
        }
        if(KEY_DOWN & keysDown()){
            cursor += 1;
        }
        cursor %= 2;
        if(alive.at(profile) != 1){
            cursor = 1;
        }
        if(KEY_A & keysDown()){
            retourne = 3+cursor;
            break;
        }
        if(KEY_B & keysDown()){
            retourne = 1;
            break;
        }
        NF_UpdateTextLayers();
    }
    if(retourne < 3){
        NF_ClearTextLayer16(1, 0);
    }
    NF_UpdateTextLayers();

    return retourne;
}

bool Title::getAction(){
    if(action == 3){
        return true;
    }
    return false;
}

Title::Title(){
    mmLoad(MOD_PASGENIAL);
    mmStart(MOD_PASGENIAL, MM_PLAY_LOOP);
    setBrightness(3, -16);
    NF_LoadTextFont16("ui/font16", "font", 256, 256, 0);
    NF_CreateTextLayer16(1, 0, 0, "font");
    loadSprites();
    loadProfileInfo();
    NF_CreateSprite(1, 2, 2, 1, 0, 0);
    action = startScreen(true);
    while(action < 3){
        switch(action){
            case 0:
                action = startScreen(false);
                break;
            case 1:
                action = profileScreen();
                break;
            case 2:
                action = menuScreen();
                break;
            default:
                break;
        }
    }
    end();
}