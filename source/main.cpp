#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "player.hpp"
#include "gfxhandler.hpp"
GfxHandler gfx;

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
	mmInitDefault("nitro:/soundbank.bin");
	NF_InitCmapBuffers();

	for(int i = 0; i < 128; i++){
		gfx.spriteMemoryMap[i] = -1;
	}
	for(int i = 0; i < 16; i++){
		gfx.paletteMemoryMap[i] = -1;
	}

    NF_LoadColisionMap("coltes", 0, 768, 768);

	NF_LoadTiledBg("cavetes", "mur", 768, 768);
	NF_CreateTiledBg(0, 0, "mur");

    Player wadedji;

    while(1){
		scanKeys();
        wadedji.updatePlayer();

		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

	return 0;
}