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
#include "player.hpp"
#include "wadedji.hpp"
#include "ennemy.hpp"
#include "pig.hpp"
#include "level.hpp"

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
    if(readText != "_PLY"){
        NF_Error(230, "d", 3);
    }
    std::getline(lvlFile, readText);
    int playerX = stoi(readText);
    std::getline(lvlFile, readText);
    int playerY = stoi(readText);
    player->updateLevel(playerX, playerY);
    std::getline(lvlFile, readText);
    if(readText != "_OBJ"){
        NF_Error(231, "d", 3);
    }
    lvlFile.close();
    update();
    update();
}

int Level::update(){
    scanKeys();
    int playerReturn = player->update();
    player->moveCamToPos(&camX, &camY, bg.getMapSizeX(), bg.getMapSizeY(), -16, 0);
	bg.scrollBg(4, oldcamX, oldcamY);
    player->updateSprite(oldcamX, oldcamY, bg.getMapSizeX(), bg.getMapSizeY());
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