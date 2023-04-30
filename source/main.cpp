#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "player.hpp"

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

    NF_LoadSpriteGfx("kirikou", 0, 16, 32);
	NF_LoadSpritePal("kirikou", 0);
	NF_VramSpriteGfx(0, 0, 0, false);
	NF_VramSpritePal(0, 0, 0);

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