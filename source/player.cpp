#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "player.hpp"

#define H_SPEED_LIMIT 2
#define H_ACC 0.5
#define H_DECELERATION 0.25
#define V_SPEED_LIMIT 5
#define V_GRAVITY_ACC 0.15
#define V_JUMP_START_SPEED -4
#define H_RUN_ACC 0.3
#define H_RUN_SPEED_LIMIT 6


Player::Player(){
    positionScreenX = 100;
    positionScreenY = 100;
    positionX = 180;
    positionY = 80;
    speedX = 0;
    speedY = 0;
    sizeX = 16;
    sizeY = 32;
    NF_CreateSprite(0, 0, 0, 0, positionScreenX, positionScreenY);
}

void Player::updateVertical(){
    if(checkRangeMapCollisionX(0, positionX, positionY+sizeY, 2) == false){
        if(speedY < 0 && !(KEY_A & keysHeld())) speedY = 0;
        accelerationY = V_GRAVITY_ACC;
        speedY += accelerationY;
        if(speedY > V_SPEED_LIMIT) speedY = V_SPEED_LIMIT;
    }
    else{
        accelerationY = 0;
        speedY = 0;
        if(KEY_A & keysDown()){
            speedY = V_JUMP_START_SPEED;
        }
    }
    if(checkRangeMapCollisionX(0, positionX, positionY, 2) == true){
        speedY = 0.1;
    }
    if(speedY > 0){
        for(int i = 0; i <= (int)speedY; i++){
            if(checkRangeMapCollisionX(0, positionX, positionY+sizeY+i, 2) == false) positionY++;
            else break;
        }
        positionY += (speedY - (int)speedY);
    }
    else positionY += speedY;
}

void Player::updateHorizontal(){
    if(speedX > H_DECELERATION) speedX -= H_DECELERATION;
    else if(speedX < -H_DECELERATION) speedX += H_DECELERATION;
    else speedX = 0;

    accelerationX = 0;
    if(KEY_L & keysDown() && accelerationY == 0){
        speedX = 0;
        run = true;
    }
    if(!(KEY_L & keysHeld())) run = false;
    if(run == false){
        if(KEY_RIGHT & keysHeld()) accelerationX += H_ACC;
        if(KEY_LEFT & keysHeld()) accelerationX -= H_ACC;
    }
    else{
        if(KEY_RIGHT & keysHeld()) accelerationX += H_RUN_ACC;
        if(KEY_LEFT & keysHeld()) accelerationX -= H_RUN_ACC;
    }

    speedX += accelerationX;
    if(run == false){
        if(speedX > H_SPEED_LIMIT) speedX = H_SPEED_LIMIT;
        if(speedX < -H_SPEED_LIMIT) speedX = -H_SPEED_LIMIT;
    }
    else{
        if(speedX > H_RUN_SPEED_LIMIT) speedX = H_RUN_SPEED_LIMIT;
        if(speedX < -H_RUN_SPEED_LIMIT) speedX = -H_RUN_SPEED_LIMIT;
    }
    
    u8 side_pixel_add = 0;
    if(speedX > 0) side_pixel_add = 16; 
    if(checkRangeMapCollisionY(0, positionX+speedX+side_pixel_add, positionY, 4) == false){
        positionX += speedX;
    }
    else{
        speedX = 0;
    }
}

void Player::updatePlayer(){
    updateVertical();
    updateHorizontal();
    moveCamToPos();
    NF_MoveSprite(0, 0, positionScreenX, positionScreenY);
}