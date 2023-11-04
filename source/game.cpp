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

#include "fileconstants.hpp"

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

void Game::loadSave(bool continuer, int profil){
    if(!continuer){
        resetSave(profil);
    }
    std::ifstream read(saveFilePath+"wade"+std::to_string(profil)+".sav");
    std::string readText;
    std::getline(read, readText);
    if(readText != "_SAV"){
        NF_Error(4000, "asd", 3);
    }
    std::getline(read, readText);
    std::getline(read, readText);
    difficulty = stoi(readText);
    std::getline(read, readText);
    std::getline(read, readText);
    currentLevel = stoi(readText);
    read.close();
}

void Game::resetSave(int profil){
    std::ofstream write(saveFilePath+"wade"+std::to_string(profil)+".sav");
    write << "_SAV" << std::endl;
    write << "1" << std::endl;
    write << std::to_string(difficulty) << std::endl;
    write << "1" << std::endl;
    write << "0" << std::endl;
    std::ifstream read("emptysave");
    std::string readText;
    for(int i = 0; i < 5; i++){
        std::getline(read, readText);
    }
    std::vector<std::string> playerData;
    while(std::getline(read, readText)){
        playerData.emplace_back(readText);
    }
    read.close();
    for(auto i : playerData){
        write << i << std::endl;
    }
    write.close();
}

Game::Game(bool continuer, int profil){
    profile = profil;
    loadSave(continuer, profile);
    //currentLevel = levelId;
    player = new Wadedji(0, 0, 0, 229, 60, &difficulty, &currentLevel, &profile);
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
        int levelOutput = 0;
        while(levelOutput == 0){
            levelOutput = level.update();
        };
        fadeOut();
        currentLevel++;
        player->saveGame();
        oldGfx = gfxName;
        if(levelOutput == 2){
            break;
        }
    }
}

Game::~Game(){
    delete player;
}