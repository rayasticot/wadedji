#include <iostream>
#include <array>
#include <unordered_map>
#include <map>
#include <functional>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "gfx.hpp"
#include "entities/entity.hpp"
#include "interface.hpp"
#include "entities/player.hpp"
#include "entities/wadedji.hpp"


Wadedji::Wadedji(int id, int sprite_, int palette_, int posx, int posy){
    spriteId = id;
    sprite = sprite_;
    palette = palette_;
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = posx;
    positionY = posy;
    speedX = 0;
    speedY = 0;
    sizeX = 32;
    sizeY = 32;
}

void Wadedji::createSprite(){
    inter.start();
    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
    spriteCreated = true;
}

void Wadedji::deleteSprite(){
    NF_DeleteSprite(0, spriteId);
    spriteCreated = false;
}

void Wadedji::updateVertical(){
    if(!checkRangeMapCollisionX(0, positionX+10, positionY+32, 2)){
        if(speedY < 0 && !(KEY_B & keysHeld())) speedY += 0.5;
        accelerationY = parameters.vGravityAcc;
        speedY += accelerationY;
        if(speedY > parameters.vSpeedLimit) speedY = parameters.vSpeedLimit;
    }
    else{
        accelerationY = 0;
        speedY = 0;
        if(KEY_B & keysDown()){
            speedY = parameters.vJumpStartSpeed;
            playSoundRandomPitch(SFX_OUI);
        }
    }
    if(checkRangeMapCollisionX(0, positionX+10, positionY+heightModif, 2)){ // Détecte plafond
        speedY = 0.1;
    }
    if(speedY > 0){
        for(int i = 0; i <= (int)speedY; i++){
            if(!checkRangeMapCollisionX(0, positionX+10, positionY+32+i, 2)) positionY++;
            else break;
        }
        positionY += (speedY - (int)speedY);
    }
    else positionY += speedY;
}

void Wadedji::updateHorizontal(){
    if(speedX > parameters.hDeceleration) speedX -= parameters.hDeceleration;
    else if(speedX < -parameters.hDeceleration) speedX += parameters.hDeceleration;
    else speedX = 0;

    accelerationX = 0;

    if(attackTime == 0){
        if(KEY_L & keysDown() && accelerationY == 0){
            speedX = 0;
            run = true;
        }
        if(!(KEY_L & keysHeld())) run = false;
        if(run == false){
            if(KEY_RIGHT & keysHeld()) accelerationX += parameters.hAcc;
            if(KEY_LEFT & keysHeld()) accelerationX -= parameters.hAcc;
        }
        else{
            if(KEY_RIGHT & keysHeld()) accelerationX += parameters.hRunAcc;
            if(KEY_LEFT & keysHeld()) accelerationX -= parameters.hRunAcc;
        }

        if(KEY_Y & keysDown() && !attackTime){
            attackTime = 20;
            if(!side){
                speedX = 4;
            }
            else{
                speedX = -4;
            }
            playSoundRandomPitch(SFX_ENVOYER);
        }
    }

    if(attackTime != 0){
        attackTime--;
    }

    speedX += accelerationX;

    if(run == false && attackTime == 0){
        if(speedX > parameters.hSpeedLimit) speedX = parameters.hSpeedLimit;
        if(speedX < -parameters.hSpeedLimit) speedX = -parameters.hSpeedLimit;
    }
    else{
        if(speedX > parameters.hRunSpeedLimit) speedX = parameters.hRunSpeedLimit;
        if(speedX < -parameters.hRunSpeedLimit) speedX = -parameters.hRunSpeedLimit;
    }

    u8 side_pixel_add = 0;
    if(speedX > 0) side_pixel_add = 14;
    if(checkRangeMapCollisionY(0, positionX+speedX+side_pixel_add+10, positionY, 4) == false){
        positionX += speedX;
    }
    else{
        speedX = 0;
    }
}

void Wadedji::updateCrouch(){
    if(speedX > parameters.hDeceleration) speedX -= parameters.hDeceleration;
    else if(speedX < -parameters.hDeceleration) speedX += parameters.hDeceleration;
    else speedX = 0;

    accelerationX = 0;
    if(KEY_RIGHT & keysHeld()) accelerationX += parameters.crouchAcc;
    if(KEY_LEFT & keysHeld()) accelerationX -= parameters.crouchAcc;

    speedX += accelerationX;

    if(speedX > parameters.crouchSpeedLimit) speedX = parameters.crouchSpeedLimit;
    if(speedX < -parameters.crouchSpeedLimit) speedX = -parameters.crouchSpeedLimit;

    u8 side_pixel_add = 0;
    if(speedX > 0) side_pixel_add = 14;
    if(checkRangeMapCollisionY(0, positionX+speedX+side_pixel_add+10, positionY+heightModif, 2) == false){
        positionX += speedX;
    }
    else{
        speedX = 0;
    }
}

void Wadedji::updateWalkAnimation(){
    if(hurtTimer){
        NF_SpriteFrame(0, spriteId, 3);
        return;
    }
    if(attackTime > 0){
        frameAnim = 4;
    }
    else if(speedY != 0){
        frameAnim = 2;
    }
    else if(speedX != 0){
        frameTime++;
        frameTime = frameTime%6;
        if(frameTime == 5){
            frameAnim++;
            frameAnim = frameAnim%4;
        }
    }
    else{
        frameAnim = 0;
        frameTime = 0;
    }

    if(speedX > 0){
        NF_HflipSprite(0, spriteId, false);
        side = 0;
    }
    else if(speedX < 0){
        NF_HflipSprite(0, spriteId, true);
        side = 1;
    }

    int actualFrame = frameAnim;
    if(actualFrame == 3) actualFrame = 1;
    if(actualFrame == 4) actualFrame = 3;

    NF_SpriteFrame(0, spriteId, actualFrame);
}

void Wadedji::updateCrouchAnimation(){
    if(speedX != 0){
        frameTime++;
        frameTime = frameTime%6;
        if(frameTime == 5){
            frameAnim++;
            frameAnim = ((frameAnim-5)%2)+5;
        }
    }
    else{
        frameAnim = 5;
        frameTime = 0;
    }
    if(speedX > 0){
        NF_HflipSprite(0, 0, false);
        side = 0;
    }
    else if(speedX < 0){
        NF_HflipSprite(0, 0, true);
        side = 1;
    }

    int actualFrame = frameAnim-1;

    NF_SpriteFrame(0, spriteId, actualFrame);
}

void Wadedji::updateWeapons(){
    if(coolDown > 0){
        coolDown--;
    }
    if(hurtTimer > 0){
        hurtTimer--;
    }
    proj = 0;
    projDamage = 0;
    for(int i = 0; i < 2; i++){
        if(weapons.at(i).itemId != inventory.at(i)){
            //if(inventory.at(i) > 0){
            weapons.at(i).loadWeapon("weapons/"+std::to_string(inventory.at(i)));
            //}
        }
    }
    if(!coolDown && !crouch){
        if(KEY_X & keysHeld() && weapons.at(0).itemId){
            if(mana >= weapons.at(0).cost){
                proj = weapons.at(0).type;
                projDamage = weapons.at(0).damage;
                mana -= weapons.at(0).cost;
                coolDown = weapons.at(0).coolDown;
                hurtTimer = 6;
            }
        }
        else if(KEY_A & keysHeld() && weapons.at(1).itemId){
            if(mana >= weapons.at(1).cost){
                proj = weapons.at(1).type;
                projDamage = weapons.at(1).damage;
                mana -= weapons.at(1).cost;
                coolDown = weapons.at(1).coolDown;
                hurtTimer = 6;
            }
        }
    }
}

void Wadedji::update(){
    if(hurtTime > 0){
        hurtTime--;
        blink = !blink;
    }
    else{
        blink = false;
    }
    if(health <= 0){
        blink = false;
    }
    timer++;
    if(attackTime == 0){
        if(KEY_DOWN & keysHeld()){
            crouch = true;
            sizeY = 16;
            heightModif = 16;
            if(frameAnim < 5){
                frameAnim = 5;
                frameTime = 0;
            }
        }
        else if(!checkRangeMapCollisionX(0, positionX+10, positionY+(sizeY/2), 2) && !(KEY_DOWN & keysDown())){
            crouch = false;
            sizeY = 32;
            heightModif = 0;
            if(frameAnim >= 5){
                frameAnim = 0;
                frameTime = 0;
            }
        }
    }
    updateVertical();
    if(!crouch){
        updateHorizontal();
        updateWalkAnimation();
    }
    else{
        updateCrouch();
        updateCrouchAnimation();
    }
    if(inter.update(health, mana, maxMana, fcfa, &inventory)){
        if(inventory.at(4) > 0){
            obtainItem(inventory.at(4));
            inventory.at(4) = 0;
        }
    }
    updateWeapons();
    if(NF_GetTile(0, positionX+16, positionY) == 2 && KEY_UP & keysDown()){
        exit = 1;
    }
    else{
        exit = 0;
    }
    if(KEY_SELECT & keysDown()){ // A RETIRER PLUS TARD SEULEMENT POUR TESTER LE JEU
        exit = 1;
    }
}

int Wadedji::getProj(){
    return proj;
}

int Wadedji::getProjDamage(){
    return projDamage * (magicDamage/2);
}

Wadedji::~Wadedji(){
    deleteSprite();
}