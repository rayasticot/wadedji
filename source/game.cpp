#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "background.hpp"
#include "object.hpp"
#include "player.hpp"
#include "wadedji.hpp"
#include "level.hpp"
#include "game.hpp"

#define F_LEVEL_LIST "level_list"

void fadeOut();
void fadeIn();


std::string Game::findLevel(std::string fileName, int levelId){
    std::ifstream lvllFile(fileName);
    std::string readText;
    std::getline(lvllFile, readText);
    if(readText != "_LVLL"){
        NF_Error(223, "d", 3);
    }
    for(int i = -1; i < levelId; i++){
        std::getline(lvllFile, readText);
    }
    lvllFile.close();

    return readText;
}

std::string Game::getGfx(std::string fileName){
    std::ifstream lvlFile(fileName);
    std::string readText;
    std::getline(lvlFile, readText);
    if(readText != "_LVL"){
        NF_Error(220, "d", 3);
    }
    std::getline(lvlFile, readText);
    lvlFile.close();

    return readText;
}

Game::Game(int levelId){
    currentLevel = levelId;
    player = new Wadedji(0, 0, 0, 229, 60);
    while(1){
        std::string currentLevelName = findLevel(F_LEVEL_LIST, currentLevel);
        std::string gfxName = getGfx(currentLevelName);
        if(gfxName != oldGfx){
            if(oldGfx != "N"){
                gfx.unloadSpr(128);
                gfx.unloadPal(16);
            }
            gfx.readGfxFile(gfxName, 0, 0, 0);
            gfx.loadSpr(128);
            gfx.loadPal(16);
            player->createSprite();
        }
        //player = std::make_unique<Player>(Wadedji(0, 0, 0, 0, 0));
        Level level(&gfx, player, currentLevelName);
        fadeIn();
        while(level.update() == 0);
        fadeOut();
        currentLevel++;
        oldGfx = gfxName;
    }
}