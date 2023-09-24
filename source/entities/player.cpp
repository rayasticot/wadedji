#include <iostream>
#include <fstream>
#include <array>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "entities/entity.hpp"
#include "interface.hpp"
#include "entities/player.hpp"


PlayerParameters::PlayerParameters(float hspeedlimit, float hacc, float hdeceleration,
    float vspeedlimit, float vgravityacc, float vjumpstartspeed, float hrunacc, float hrunspeedlimit)
{
    hSpeedLimit = hspeedlimit;
    hAcc = hacc;
    hDeceleration = hdeceleration;
    vSpeedLimit = vspeedlimit;
    vGravityAcc = vgravityacc;
    vJumpStartSpeed = vjumpstartspeed;
    hRunAcc = hrunacc;
    hRunSpeedLimit = hrunspeedlimit;
}

void Player::updateLevel(int x, int y){
    positionX = x;
    positionY = y;
}

void Player::hurt(int damage, float direction){
    health -= damage;
    if(health < 0){
        health = 0;
    }
    speedX = direction*(damage*2);
    hurtTime = 60;
    playSoundRandomPitch(SFX_AIE);
}

void Player::obtainItem(int item){
    if(!item){
        return;
    }
    if(!effectIndex.at(item-1) || !itemIndex.at(item-1)){
        applyItemEffect(item);
    }
    if(!itemIndex.at(item-1)){
        itemIndex.at(item-1) = true;
    }
}

void Player::applyItemEffect(int item){
    std::ifstream lvllFile("itemeffects/" + std::to_string(item));
    std::string readText;
    std::getline(lvllFile, readText);
    if(readText != "_ITM"){
        NF_Error(2323, "sad", 2);
    }
    std::getline(lvllFile, readText);
    while(readText != "\\"){
        int* changeValue = &health;
        int limitValue = 999999;
        switch(readText.data()[0]){
            case 'h':
                changeValue = &health;
                limitValue = maxHealth;
                break;
            case 'm':
                changeValue = &mana;
                limitValue = maxMana;
                break;
            case 'f':
                changeValue = &fcfa;
                break;
            case 'H':
                changeValue = &maxHealth;
                break;
            case 'M':
                changeValue = &maxMana;
                break;
            case 'd':
                changeValue = &meleeDamage;
                break;
            case 'D':
                changeValue = &magicDamage;
                break;
            default:
                NF_Error(3443, "das", 2);
                break;
        }
        std::getline(lvllFile, readText);
        const char sign = readText.data()[0];
        std::getline(lvllFile, readText);
        int amount = stoi(readText);
        int total = 0;
        switch(sign){
            case '+':
                total = *changeValue+amount;
                if(total <= limitValue){
                    *changeValue = total;
                }
                break;
            case '-':
                total = *changeValue-amount;
                if(total <= limitValue){
                    *changeValue = total;
                }
                break;
            case '=':
                if(amount <= limitValue){
                    *changeValue = amount;
                }
                break;
        }
        std::getline(lvllFile, readText);
        std::getline(lvllFile, readText);
    }
    lvllFile.close();
}