#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <functional>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "background.hpp"
#include "entities/entity.hpp"
#include "item.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/wadedji.hpp"
#include "entities/grounditem.hpp"
#include "entities/ennemy.hpp"
#include "entities/pig.hpp"
#include "entities/marabout.hpp"
#include "entities/projectile.hpp"
#include "level.hpp"
#include "game.hpp"

#define F_LEVEL_LIST "level_list"

void fadeOut();
void fadeIn();
int getMod(uint musicId);

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

uint Game::getMusic(std::string fileName){
    std::ifstream lvlFile(fileName);
    std::string readText;
    std::getline(lvlFile, readText);
    if(readText != "_LVL"){
        NF_Error(251, "d", 3);
    }
    std::getline(lvlFile, readText);
    std::getline(lvlFile, readText);
    std::getline(lvlFile, readText);
    lvlFile.close();

    return stoi(readText);
}

Game::Game(int levelId){
    currentLevel = levelId;
    player = new Wadedji(0, 0, 0, 229, 60);
    mmLoadEffect(SFX_HURT);
    mmLoadEffect(SFX_OUI);
    mmLoadEffect(SFX_ENVOYER);
    mmLoadEffect(SFX_AIE);
    mmLoadEffect(SFX_CASH);
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
        music = getMusic(currentLevelName);
        if(music != oldMusic){
            if(oldMusic != 22960){
                mmStop();
                mmUnload(getMod(oldMusic));
            }
            mmLoad(getMod(music));
            mmStart(getMod(music), MM_PLAY_LOOP);
            oldMusic = music;
        }
        fadeIn();
        while(level.update() == 0);
        fadeOut();
        currentLevel++;
        oldGfx = gfxName;
    }
}

Game::~Game(){
    delete player;
}