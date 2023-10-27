#include <iostream>
#include <fstream>
#include <memory>
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
#include "entities/basictrajproj.hpp"
#include "entities/sintrajproj.hpp"
#include "level.hpp"

#define ENN_PIG 0
#define ENN_MARA_F 1
#define ENN_MARA_T 2

#define PIG_SPR 2
#define MARA_F_SPR 3
#define MARA_T_SPR 4
#define PROJ_SPR 5


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
    std::getline(lvlFile, readText);
    while(readText != "\\"){
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
            groundItemPool.loadPoolFile("pools/"+std::to_string(health));
            int item = groundItemPool.giveItem();
            int projId = findIdItem();
            groundItems.at(projId).reset(new GroundItem(projId+112, 1, 1, positionX, positionY, item));
            break;
        }
        case ENN_PIG:
            ennemyVector.emplace_back(new Pig(id, PIG_SPR, 2, positionX, positionY, health));
            break;
        case ENN_MARA_F:
            ennemyVector.emplace_back(new Marabout(id, MARA_F_SPR, 2, positionX, positionY, health, 1));
            break;
        case ENN_MARA_T:
            ennemyVector.emplace_back(new Marabout(id, MARA_T_SPR, 2, positionX, positionY, health, 2));
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

int Level::findIdPlayer(){
    for(int i = 0; i < 24; i++){
        if(playerProj.at(i) == NULL){
            return i;
        }
    }
    NF_Error(6553, "das", 2);
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
    for(auto& i : playerProj){
        if(i == NULL) continue;
        if(i->update()){
            int projId = i->getId()-88;
            playerProj.at(projId) = NULL;
        }
        projCounter++;
    }
    for(auto& i : groundItems){
        i->update();
    }
}

void Level::updateGfx(){
    player->moveCamToPos(&camX, &camY, bg.getMapSizeX(), bg.getMapSizeY(), -16, 0+(32-player->getSizeY()));
	bg.scrollBg(4, oldcamX, oldcamY);
    player->updateSprite(oldcamX, oldcamY, bg.getMapSizeX(), bg.getMapSizeY());
    for(auto& i : ennemyVector){
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    for(auto& i : ennemyProj){
        if(i == NULL) continue;
        i->updateSprite(camX, camY, bg.getMapSizeX(), bg.getMapSizeY());
    }
    for(auto& i : playerProj){
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
            {
                int projId = findIdEnnemy();
                bool ennemySide = player->getPosX()-(i->getPosX()) < 0;
                NF_HflipSprite(0, i->getId(), ennemySide);
                int posAdd = 24;
                if(ennemySide) posAdd = 8;
                ennemyProj.at(projId).reset(new SinTrajProj(projId+64, PROJ_SPR, 3, i->getPosX()+posAdd, i->getPosY()+0, i->getPosX()+posAdd-(i->getPosX()+posAdd-(player->getPosX()+posAdd)), i->getPosY()+0, 2, 1, 1, 15));
                break;
            }
            case 2:
            {
                int projId = findIdEnnemy();
                bool ennemySide = player->getPosX()-(i->getPosX()) < 0;
                bool ennemySideY = player->getPosY()-(i->getPosY()) < 0;
                NF_HflipSprite(0, i->getId(), ennemySide);
                int posAdd = 24;
                if(ennemySide) posAdd = 8;
                int xAdd = 1;
                if(ennemySide) xAdd = -1;
                int yAdd = 1;
                if(ennemySideY) yAdd = -1;
                ennemyProj.at(projId).reset(new SinTrajProj(projId+64, PROJ_SPR, 3, i->getPosX()+posAdd, i->getPosY()+0, i->getPosX()+posAdd+xAdd, i->getPosY()+0+yAdd, 2, 1, 1, 15));
                break;
            }
        }
    }
}

void Level::checkPlayerProj(){
    switch(player->getProj()){
        case 0:
            break;
        case 1:
        {
            int projId = findIdPlayer();
            bool side = player->getSide();
            int posAdd = 24;
            if(side) posAdd = 8;
            int trajAdd = 1;
            if(side) trajAdd = -1;
            playerProj.at(projId).reset(new SinTrajProj(projId+88, PROJ_SPR, 3, player->getPosX()+posAdd, player->getPosY()+12, player->getPosX()+trajAdd+posAdd, player->getPosY()+12, 3, player->getProjDamage(), 1, 15));
            break;
        }
    }
}

void Level::checkGroundItem(){
    for(auto& i : groundItems){
        if(i == NULL) continue;
        if(i->checkHit(player) && !i->getWait()){
            if(player->setupItem(i->getItemId())){
                int groundItemId = i->getId()-112;
                groundItems.at(groundItemId) = NULL;
            }
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
                        player->giveMana(5);
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

void Level::checkHurtPlayerProj(){
    float playerDirection = 1.0;
    if(player->getSide()){
        playerDirection = -1.0;
    }
    for(auto& proj : playerProj){
        for(auto& ennemy : ennemyVector){
            switch(proj->checkHit(ennemy.get())){
                case 0:
                    break;
                case 1:
                    if(ennemy->getHurtTime() <= 0){
                        ennemy->hurt(proj->getDamage(), playerDirection);
                        if(ennemy->getHealth() <= 0 && ennemy->alive){
                            ennemy->alive = false;
                            int item = pools.at(ennemy->getType()).giveItem();
                            if(item){
                                int projId = findIdItem();
                                groundItems.at(projId).reset(new GroundItem(projId+112, 1, 1, ennemy->getPosX(), ennemy->getPosY(), item));
                            }
                        }
                    }
                    if(ennemy->alive){
                        proj->kill();
                    }
                    break;
            }
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
    checkPlayerProj();
    checkGroundItem();
    checkHurtEnnemy();
    checkHurtPlayerProj();
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