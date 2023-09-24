#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "entities/entity.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/wadedji.hpp"
#include "entities/grounditem.hpp"
#include "entities/ennemy.hpp"
#include "entities/pig.hpp"
#include "gfx.hpp"
#include "background.hpp"
#include "entities/projectile.hpp"
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
	const int music[sizeMusArray] = {MOD_PLANETEZER2, MOD_BLOQUER};
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

	Game game(0);

	return 0;
}