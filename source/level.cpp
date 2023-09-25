#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "background.hpp"
#include "entities/entity.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/wadedji.hpp"
#include "entities/grounditem.hpp"
#include "entities/ennemy.hpp"
#include "entities/pig.hpp"
#include "entities/marabout.hpp"
#include "entities/projectile.hpp"
#include "entities/basictrajproj.hpp"
#include "level.hpp"

#define ENN_PIG 0
#define ENN_MARA 1

#define PIG_SPR 2
#define PROJ_SPR 3


PoolItem::PoolItem(int id, int rate){
    itemId = id;
    dropRate = rate;
}

void DropPool::loadPoolFile(std::string fileName){
    if(loaded){
        return;
    }
    loaded = true;
    std::ifstream lvlFile(fileName);
    std::string readText;
    std::getline(lvlFile, readText);
    if(readText != "_POL"){
        NF_Error(22929, "d", 3);
    }
    int index = 0;
    int totalRate = 0;
    while(readText != "\\"){
        std::getline(lvlFile, readText);
        int itemId = stoi(readText);
        std::getline(lvlFile, readText);
        int dropRate = stoi(readText);
        if(dropRate <= 0){
            NF_Error(2242, "asd", 3);
        }
        totalRate += dropRate;
        if(totalRate > 100){
            NF_Error(12344, "asd", 3);
        }
        items.emplace_back(PoolItem(itemId, dropRate));
        index += 1;
        if(index >= 100){
            NF_Error(31999, "asd", 3);
        }
        std::getline(lvlFile, readText);
        std::getline(lvlFile, readText);
    }
    lvlFile.close();
}

int DropPool::giveItem(){
    int drop = rand()%100;
    int index = 0;
    for(auto& i : items){
        if(drop >= index && drop <= index+i.dropRate){
            return i.itemId;
        }
        index += i.dropRate;
    }

    return 0;
}

void Level::addEnnemy(int type, int positionX, int positionY, int health, int id){
    switch(type){
        case -1:
            {
                int projId = findIdItem();
                groundItems.at(projId).reset(new GroundItem(projId+112, 1, 1, positionX, positionY, health));
                break;
            }
        case ENN_PIG:
            ennemyVector.emplace_back(new Pig(id, PIG_SPR, 2, positionX, positionY, health));
            break;
        case ENN_MARA:
            ennemyVector.emplace_back(new Marabout(id, PIG_SPR, 2, positionX, positionY, health));
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
        std::getline(lvlFile, readText);
        int health = stoi(readText);
        addEnnemy(ennemyType, ennemyX, ennemyY, health, sprId);
        sprId++;
        std::getline(lvlFile, readText);
        if(readText != ":"){
            break;
        }
        std::getline(lvlFile, readText);
    }
    lvlFile.close();
    for(int i = 0; i < 2; i++){
        pools.at(i).loadPoolFile("pools/"+std::to_string(i));
    }
    update();
    update();
}

int Level::findIdEnnemy(){
    for(int i = 0; i < 24; i++){
        if(ennemyProj.at(i) == NULL){
            return i;
        }
    }
    NF_Error(655, "das", 2);
    return 229;
}

int Level::findIdItem(){
    for(int i = 0; i < 16; i++){
        if(groundItems.at(i) == NULL){
            return i;
        }
    }
    NF_Error(6552, "das", 2);
    return 229;
}

void Level::freeze(){
    while(sleep > 0){
        swiWaitForVBlank();
        sleep--;
    }
}

void Level::updateEntities(){
    player->update();
    activeEffect.applyActive(*player);
    for(auto& i : ennemyVector){
        i->update();
    }
    int projCounter = 0;
    for(auto& i : ennemyProj){
        if(i == NULL) continue;
        if(i->update()){
            int projId = i->getId()-64;
            ennemyProj.at(projId) = NULL;
        }
        projCounter++;
    }
    for(auto& i : groundItems){
        i->update();
    }
}

void Level::updateGfx(){
    player->moveCamToPos(&camX, &camY, bg.getMapSizeX(), bg.getMapSizeY(), -16, 0);
	bg.scrollBg(4, oldcamX, oldcamY);
    player->updateSprite(oldcamX, oldcamY, bg.getMapSizeX(), bg.getMapSizeY());
    for(auto& i : ennemyVector){
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    for(auto& i : ennemyProj){
        if(i == NULL) continue;
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    for(auto& i : groundItems){
        if(i == NULL) continue;
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    oldcamX = camX;
	oldcamY = camY;
}

void Level::checkProj(){
    for(auto& i : ennemyVector){
        if(i == NULL) continue;
        switch(i->getProj()){
            case 0:
                break;
            case 1:
                int projId = findIdEnnemy();
                ennemyProj.at(projId).reset(new BasicTrajProj(projId+64, PROJ_SPR, PROJ_SPR, i->getPosX(), i->getPosY(), player->getPosX()+16, player->getPosY()+16, 2, 1));
                break;
        }
    }
}

void Level::checkGroundItem(){
    for(auto& i : groundItems){
        if(i == NULL) continue;
        if(i->checkHit(player) && !i->getWait()){
            player->obtainItem(i->getItemId());
            int groundItemId = i->getId()-112;
            groundItems.at(groundItemId) = NULL;
        }
    }
}

void Level::checkHurtEnnemy(){
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
                        //sleep = 5;
                    }
                    player->hurt(i->getMeleeDamage(), 0);
                }
                break;
            case 2:
                if(i->getHurtTime() <= 0){
                    i->hurt(player->getMeleeDamage(), playerDirection);
                    if(i->getHealth() <= 0 && i->alive){
                        i->alive = false;
                        int item = pools.at(i->getType()).giveItem();
                        if(item){
                            int projId = findIdItem();
                            groundItems.at(projId).reset(new GroundItem(projId+112, 1, 1, i->getPosX(), i->getPosY(), item));
                        }
                    }
                    mmEffect(SFX_HURT);
                }
                break;
        }
    }
}

void Level::checkHurtProj(){
    /*
    float playerDirection = 1.0;
    if(player->getSide()){
        playerDirection = -1.0;
    }
    */
    for(auto& i : ennemyProj){
        switch(i->checkHit(player)){
            case 0:
                break;
            case 1:
                if(player->getHurtTime() <= 0){
                    if(player->getHealth() > 0){
                        //sleep = 5;
                    }
                    player->hurt(i->getDamage(), 0);
                    i->kill();
                }
                break;
        }
    }
}

void Level::screenRefresh(){
    NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	swiWaitForVBlank();

	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
}

int Level::update(){
    scanKeys();
    freeze();
    updateEntities();
    checkProj();
    checkGroundItem();
    checkHurtEnnemy();
    checkHurtProj();
    updateGfx();

    screenRefresh();

    return player->getExit();
}

Level::Level(GfxGroup* gfxGroup, Player* play, std::string fileName){
    gfx = gfxGroup;
    player = play;
    readLevelFile(fileName);
}