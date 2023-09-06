#include <iostream>
#include <cmath>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "wadedji.hpp"


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

    inter.start();
}

void Wadedji::createSprite(){
    NF_CreateSprite(0, spriteId, sprite, palette, positionScreenX, positionScreenY);
}

void Wadedji::deleteSprite(){
    NF_DeleteSprite(0, spriteId);
}

void Wadedji::updateVertical(){
    if(checkRangeMapCollisionX(0, positionX+10, positionY+sizeY, 2) == false){
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
            mm_sfxhand jumpSound = mmEffect(SFX_OUI);
            int rate = 1024 * std::pow(2, ((rand()%9)-4)/24.0);
            mmEffectRate(jumpSound, rate);
        }
    }
    if(checkRangeMapCollisionX(0, positionX+10, positionY, 2) == true){
        speedY = 0.1;
    }
    if(speedY > 0){
        for(int i = 0; i <= (int)speedY; i++){
            if(checkRangeMapCollisionX(0, positionX+10, positionY+sizeY+i, 2) == false) positionY++;
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
            mm_sfxhand punchSound = mmEffect(SFX_ENVOYER);
            int rate = 1024 * std::pow(2, ((rand()%9)-4)/24.0);
            mmEffectRate(punchSound, rate);
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

void Wadedji::updateAnimation(){
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
        NF_HflipSprite(0, 0, false);
        side = 0;
    }
    else if(speedX < 0){
        NF_HflipSprite(0, 0, true);
        side = 1;
    }

    int actualFrame = frameAnim;
    if(actualFrame == 3) actualFrame = 1;
    if(actualFrame == 4) actualFrame = 3;

    NF_SpriteFrame(0, spriteId, actualFrame);
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
    updateVertical();
    updateHorizontal();
    updateAnimation();
    inter.update(health);
    if(NF_GetTile(0, positionX+16, positionY) == 2 && KEY_UP & keysDown()){
        exit = 1;
    }
    else{
        exit = 0;
    }
}