#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "background.hpp"
#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "wadedji.hpp"
#include "ennemy.hpp"
#include "pig.hpp"
#include "level.hpp"

#define ENN_PIG 0

#define PIG_SPR 1


void Level::addEnnemy(int type, int positionX, int positionY, int id){
    switch(type){
        case 0:
            ennemyVector.emplace_back(new Pig(id, PIG_SPR, 1, positionX, positionY));
            break;
    }
}

void Level::setUpBg(){
    bg.loadCol();
	bg.loadBg(4);
	bg.createBg(4);
}

void Level::readLevelFile(std::string fileName){
    std::ifstream lvlFile(fileName);
    std::string readText;
    std::getline(lvlFile, readText);
    if(readText != "_LVL"){
        NF_Error(228, "d", 3);
    }
    std::getline(lvlFile, readText);
    std::getline(lvlFile, readText);
    bg.readBackgroundFile(readText);
    setUpBg();
    std::getline(lvlFile, readText);
    std::getline(lvlFile, readText);
    if(readText != "_PLY"){
        NF_Error(230, "d", 3);
    }
    std::getline(lvlFile, readText);
    int playerX = stoi(readText);
    std::getline(lvlFile, readText);
    int playerY = stoi(readText);
    player->updateLevel(playerX, playerY);
    std::getline(lvlFile, readText);
    if(readText != "_ENN"){
        NF_Error(231, "d", 3);
    }
    
    int sprId = 1;
    std::getline(lvlFile, readText);
    while(readText != "\\"){
        int ennemyType = stoi(readText);
        std::getline(lvlFile, readText);
        int ennemyX = stoi(readText);
        std::getline(lvlFile, readText);
        int ennemyY = stoi(readText);
        addEnnemy(ennemyType, ennemyX, ennemyY, sprId);
        sprId++;
        std::getline(lvlFile, readText);
        if(readText != ":"){
            break;
        }
        std::getline(lvlFile, readText);
    }
    lvlFile.close();
    update();
    update();
}

int Level::update(){
    while(sleep > 0){
        swiWaitForVBlank();
        sleep--;
    }
    scanKeys();
    player->update();
    int playerReturn = player->getExit();
    for(auto& i : ennemyVector){
        i->update();
    }
    player->moveCamToPos(&camX, &camY, bg.getMapSizeX(), bg.getMapSizeY(), -16, 0);
	bg.scrollBg(4, oldcamX, oldcamY);
    player->updateSprite(oldcamX, oldcamY, bg.getMapSizeX(), bg.getMapSizeY());
    for(auto& i : ennemyVector){
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    float playerDirection = 1.0;
    if(player->getSide()){
        playerDirection = -1.0;
    }
    for(auto& i : ennemyVector){
        switch(i->checkHit(player)){
            case 0:
                break;
            case 1:
                if(player->getHurtTime() <= 0 && i->getHurtTime() <= 0){
                    if(player->getHealth() > 0){
                        sleep = 5;
                    }
                    player->hurt(i->getMeleeDamage(), 0);
                    mmEffect(SFX_HURT);
                }
                break;
            case 2:
                if(i->getHurtTime() <= 0){
                    if(i->getHealth() > 0){
                        sleep = 5;
                    }
                    i->hurt(player->getMeleeDamage(), playerDirection);
                    mmEffect(SFX_HURT);
                }
                break;
        }
    }
    oldcamX = camX;
	oldcamY = camY;

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	swiWaitForVBlank();

	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

    return playerReturn;
}

Level::Level(GfxGroup* gfxGroup, Player* play, std::string fileName){
    gfx = gfxGroup;
    player = play;
    readLevelFile(fileName);
}