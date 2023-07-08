#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "caca.hpp"

Caca::Caca(int id, int sprite, int palette, int posx, int posy){
    spriteId = id;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    sizeX = 16;
    sizeY = 32;

    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
}

void Caca::update(){

}