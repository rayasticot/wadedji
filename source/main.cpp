#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "wadedji.hpp"
#include "ennemy.hpp"
#include "pig.hpp"
#include "gfx.hpp"
#include "background.hpp"
#include "projectile.hpp"
#include "level.hpp"
#include "game.hpp"

void crashGame(std::string message){
	consoleDemoInit();
	consoleClear();
	iprintf(message.data());
	while(1){}
}

int getMod(uint musicId){
	const int sizeMusArray = 2;
	const int music[sizeMusArray] = {MOD_PLANETEZER2, 0};
	if(musicId >= sizeMusArray) NF_Error(270, "asd", 4);

	return music[musicId];
}

int main(int argc, char **argv){
    NF_Set2D(0, 0);
	NF_Set2D(1, 0);
	NF_SetRootFolder("NITROFS");
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	mmInitDefault(std::string("nitro:/soundbank.bin").data());
	mmSelectMode(MM_MODE_C);
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
	NF_InitCmapBuffers();
	setBrightness(3, -16);

	Game game(3);

	/*
	GfxGroup testGfx;
	testGfx.readGfxFile("grotte.gfxjim", 0, 0, 0);
	testGfx.loadSpr(128);
	testGfx.loadPal(16);

	Wadedji wade(0, 0, 0, 0, 0);

	Level level(&testGfx, &wade, "level0/lvl.lvljim");
	
	while(1){
		level.update();
	}
	*/

	/*
    LevelBackground testBg("level3/bg.bgjim");
	testBg.loadCol();
	testBg.loadBg(4);
	testBg.createBg(4);
	GfxGroup testGfx("grotte.gfxjim", 0, 0, 0);
	testGfx.loadSpr(128);
	testGfx.loadPal(16);

	std::vector<std::function<void()>> update;
	std::vector<std::function<void(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY)>> updateSprite;

	std::vector<std::unique_ptr<Object>> objectVector;
	objectVector.emplace_back(new Wadedji(0, 0, 0, 120, 0));
	objectVector.emplace_back(new Pig(1, 1, 1, 384, 192));

	int camX = 0;
	int camY = 0;
	int oldcamX = camX;
	int oldcamY = camY;

    while(1){
		scanKeys();
		for(auto& i : objectVector){
            i->update();
        }
		objectVector.at(0)->moveCamToPos(&camX, &camY, testBg.getMapSizeX(), testBg.getMapSizeY());
		testBg.scrollBg(4, oldcamX, oldcamY);
		for(auto& i : objectVector){
            i->updateSprite(oldcamX, oldcamY, testBg.getMapSizeX(), testBg.getMapSizeY());
        }
		oldcamX = camX;
		oldcamY = camY;
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}
	*/

	return 0;
}