#include <iostream>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "player.hpp"
#include "caca.hpp"
#include "gfx.hpp"
#include "background.hpp"

void crashGame(std::string message){
	consoleDemoInit();
	consoleClear();
	iprintf(message.data());
	while(1){}
}

int main(int argc, char **argv){
    NF_Set2D(0, 0);
	NF_Set2D(1, 0);
	NF_SetRootFolder("NITROFS");
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);
	mmInitDefault(std::string("nitro:/soundbank.bin").data());
	NF_InitCmapBuffers();

    LevelBackground testBg("bgfile.bgjim");
	testBg.loadCol();
	testBg.loadBg(4);
	testBg.createBg(4);
	GfxGroup testGfx("gfxfile.gfxjim", 0, 0, 0);
	testGfx.loadSpr(128);
	testGfx.loadPal(16);

    Player wadedji(0, 0, 0, 180, 100);
	Caca caca(1, 1, 1, 100, 100);

	int camX = 0;
	int camY = 0;
	int oldcamX = camX;
	int oldcamY = camY;

    while(1){
		scanKeys();
		wadedji.update();
		caca.update();
		wadedji.moveCamToPos(&camX, &camY, testBg.getMapSizeX(), testBg.getMapSizeY());
		testBg.scrollBg(4, oldcamX, oldcamY);
		wadedji.updateSprite(oldcamX, oldcamY, testBg.getMapSizeX(), testBg.getMapSizeY());
		caca.updateSprite(oldcamX, oldcamY, testBg.getMapSizeX(), testBg.getMapSizeY());
		oldcamX = camX;
		oldcamY = camY;
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

	return 0;
}