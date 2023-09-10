#include <iostream>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "object.hpp"
#include "interface.hpp"
#include "player.hpp"


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