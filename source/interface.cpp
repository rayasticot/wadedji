#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "interface.hpp"


void InterfaceItem::start(int posX, int posY, int spriteid, int itemid){
    positionX = posX;
    positionY = posY;
    defaultPositionX = posX;
    defaultPositionY = posY;
    spriteId = spriteid;
    itemId = itemid;

    NF_CreateSprite(1, spriteId, 1, 1, positionX, positionY);
    NF_SpriteFrame(1, spriteId, itemId+2);
    started = true;
}

InterfaceItem::~InterfaceItem(){
    if(started){
        NF_DeleteSprite(1, spriteId);
    }
}

bool InterfaceItem::isTouched(int px, int py){
    if(px >= positionX-16 && px < positionX+32){
        if(py >= positionY-16 && py < positionY+32){
            return true;
        }
    }
    return false;
}

void InterfaceItem::resetPos(){
    positionX = defaultPositionX;
    positionY = defaultPositionY;
}

void InterfaceItem::updateSprite(){
    NF_SpriteFrame(1, spriteId, itemId+2);
    NF_MoveSprite(1, spriteId, positionX, positionY);
}

void Interface::start(){
    NF_LoadTilesForBg("ui/bottomtilemap", "bottommap", 256, 256, 0, 11);
    NF_CreateTiledBg(1, 1, "bottommap");
    NF_LoadTextFont16("ui/font16", "font", 256, 256, 0);
    NF_CreateTextLayer16(1, 0, 0, "font");
    NF_LoadTiledBg("ui/fonneutre", "fond", 256, 256);
    NF_CreateTiledBg(1, 3, "fond");

    NF_LoadSpriteGfx("ui/spr/rond", 128, 64, 64);
    NF_VramSpriteGfx(1, 128, 0, false);
    NF_LoadSpriteGfx("ui/spr/trash", 127, 32, 32);
    NF_VramSpriteGfx(1, 127, 2, false);
    NF_LoadSpritePal("ui/pal/bottomui", 16);
    NF_VramSpritePal(1, 16, 0);
    //NF_LoadSpriteGfx("ui/spr/test", 127, 32, 32);
    NF_VramSpriteGfx(1, 1, 1, false);
    NF_VramSpritePal(1, 1, 1);

    for(int i = 0; i < 5; i++){
        NF_CreateSprite(1, i+5, 0, 0, itemPositions.positions_x.at(i), itemPositions.positions_y.at(i));
        items.at(i).start(itemPositions.positions_x.at(i)+16, itemPositions.positions_y.at(i)+16, i, 0);
    }
    NF_CreateSprite(1, 11, 0, 0, itemPositions.positions_x.at(5), itemPositions.positions_y.at(5));
    NF_CreateSprite(1, 10, 2, 0, 97, 135);
    items.at(2).itemId = -2;
    items.at(3).itemId = -1;
    NF_SpriteFrame(1, 7, 1);
    NF_SpriteFrame(1, 8, 1);
    NF_SpriteFrame(1, 11, 1);
}

void Interface::drawHealth(int health){
    for(int i = 0; i < 32; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 0);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 0);
    }
    for(int i = 0; i < health; i++){
        NF_SetTileOfMap(1, 1, i, (i/16), 1);
        NF_SetTileOfMap(1, 1, i, (i/16)+1, 2);
    }
}

void Interface::drawMana(int mana, int maxMana){
    for(int i = 0; i < 10; i++){
        NF_SetTileOfMap(1, 1, 9-i, 4, 11);
    }
    if(mana > 0){
        int mana80 = ((float)mana/(float)maxMana)*80;
        int manaNumber = mana80/8;
        for(int i = 0; i < manaNumber; i++){
            NF_SetTileOfMap(1, 1, 9-i, 4, 3);
        }
        int manaFirst = mana80%8;
        if(manaFirst){
            NF_SetTileOfMap(1, 1, 9-manaNumber, 4, 11-manaFirst);
        }
    }
}

void Interface::drawFcfa(int fcfa){
    std::string argent = std::to_string(fcfa)+" FCFA";
    NF_WriteText16(1, 0, 0, 3, argent.data());
}

void Interface::readItemDesc(std::string fileName){
    std::ifstream lvlFile(fileName);
    std::getline(lvlFile, itemDesc);
    lvlFile.close();
}

void Interface::drawItemDesc(int item){
    if(item != lastItem){
        readItemDesc("itemdesc/"+std::to_string(item));
        lastItem = item;
    }
    NF_WriteText16(1, 0, 0, 11, itemDesc.data());
}

bool Interface::updateHolding(std::array<int, 5>* inventory){
    for(int i = 0; i < 5; i++){
        items.at(i).itemId = inventory->at(i);
        items.at(i).updateSprite();
    }
    if(KEY_TOUCH & keysHeld()){
        last_px = touch.px;
        last_py = touch.py;
        if(heldTimer >= 3){
            items.at(currentHeld).positionX = touch.px-8;
            items.at(currentHeld).positionY = touch.py-8;
        }
        else{
            for(int i = 0; i < 5; i++){
                if(items.at(i).isTouched(touch.px, touch.py)){
                    if(currentHeld == i){
                        heldTimer++;
                    }
                    else{
                        heldTimer = 0;
                    }
                    currentHeld = i;
                    if(items.at(i).itemId >= 1){
                        if(effectIndex.at(items.at(i).itemId-1) != 3){
                            return true;
                        }
                    }
                    break;
                }
            }
        }
    }
    else{
        heldTimer = 0;
        for(int i = 0; i < 5; i++){
            if(i == currentHeld){
                items.at(i).resetPos();
                continue;
            }
            if(items.at(i).isTouched(last_px, last_py)){
                if(currentHeld == 2 || currentHeld == 3/*inventory->at(currentHeld) <= 0 || inventory->at(i) <= 0*/){
                    break;
                }
                if(i == 2 || i == 3){
                    break;
                }
                int tempItem = inventory->at(currentHeld);
                inventory->at(currentHeld) = inventory->at(i);
                inventory->at(i) = tempItem;
            }
        }
        if(last_px >= itemPositions.positions_x.at(5)-16 && last_px < itemPositions.positions_x.at(5)+32){
            if(last_py >= itemPositions.positions_y.at(5)-16 && last_py < itemPositions.positions_y.at(5)+32){
                if(currentHeld != 2 && currentHeld != 3){
                    inventory->at(currentHeld) = 0;
                }
            }
        }
        last_px = -1;
        last_py = -1;
    }
    const std::array<int, 3> slots = {0, 1, 4};

    for(auto i : slots){
        if(inventory->at(i) > 0){
            NF_SpriteFrame(1, 5+i, rarityIndex.at(inventory->at(i)-1));
        }
        else{
            NF_SpriteFrame(1, 5+i, 0);
        }
    }

    return false;
}

bool Interface::update(int health, int mana, int maxMana, int fcfa, std::array<int, 5>* inventory){
    bool retourne = false;
    touchRead(&touch);
    NF_ClearTextLayer(1, 0);
    drawHealth(health);
    drawMana(mana, maxMana);
    drawFcfa(fcfa);
    retourne = updateHolding(inventory);
    drawItemDesc(inventory->at(4));
    NF_UpdateVramMap(1, 1);
    NF_UpdateTextLayers();

    return retourne;
}