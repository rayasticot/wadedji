#include <iostream>
#include <fstream>
#include <memory>
#include <functional>
#include <vector>
#include <map>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "entities/entity.hpp"
#include "item.hpp"
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
#include "title.hpp"
#include "cinematic.hpp"

#include "fileconstants.hpp"


void crashGame(std::string message){
	consoleDemoInit();
	consoleClear();
	iprintf(message.data());
	while(1){}
}

int getMod(uint musicId){
	const int sizeMusArray = 3;
	const int music[sizeMusArray] = {MOD_PLANETEZER2, MOD_BLOQUER, MOD_ATTAQUE};
	if(musicId >= sizeMusArray) NF_Error(270, "asd", 4);

	return music[musicId];
}

void createSave(int profil){
	if(profil > 2 || profil < 0){
		return;
	}
	std::ifstream read(saveFilePath+"wade"+std::to_string(profil)+".sav");
	if(read.good()){
		read.close();
		return;
	}
	read.close();

	std::ifstream defaultsave("emptysave");
	std::ofstream write(saveFilePath+"wade"+std::to_string(profil)+".sav");
	std::string readText;
	while(getline(defaultsave, readText)){
		write << readText << std::endl;
	}
	write.close();
	defaultsave.close();
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
	NF_InitTextSys(1);
	//fatInitDefault();
	for(int i = 0; i < 3; i++){
		createSave(i);
	}
	{
		Cinematic cinema("cinematic/intro");
		cinema.play();
	}
	while(1){
		Title title;
		Game game(title.getAction(), title.getProfil());
	}

	return 0;
}