#include <iostream>
#include <vector>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "inventory.hpp"

/*
void Inventory::takeItem(int id, bool type){
    if(type){
        activeItemIndex.at(id) = true;
    }
    else{
        passiveItemIndex.at(id) = true;
    }
}

void Inventory::switchWeapon(int slot1, int slot2){
    int item1 = weapons.at(slot1);
    weapons.at(slot1) = weapons.at(slot2);
    weapons.at(slot2) = item1;
}
*/