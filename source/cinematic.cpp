#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <nds.h>
#include <nf_lib.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "cinematic.hpp"


CinematicFrame::CinematicFrame(std::string imag, std::string name, int tim, int scroll, int trans){
    image = imag;
    time = tim;
    bgName = name;
    time = tim;
    scrollEffect = scroll;
    transition = trans;
}

void CinematicFrame::load(){
    loaded = true;
    NF_LoadTiledBg(image.data(), bgName.data(), 512, 512);
}

void CinematicFrame::unLoad(){
    if(loaded){
        loaded = false;
        NF_UnloadTiledBg(bgName.data());
    }
}

void CinematicFrame::create(){
    created = true;
    NF_CreateTiledBg(0, 0, bgName.data());
}

void CinematicFrame::destroy(){
    if(created){
        created = false;
        NF_DeleteTiledBg(0, 0);
    }
}

int CinematicFrame::addCalcX(int timer){
    if(time-timer < 60){
        switch(transition){
            case 0:
                break;
            case 1:
                return (int)(fixedToFloat(tanLerp(degreesToAngle((60-(time-timer))*1.5)), 12)*22);
                break;
        }
    }
    switch(scrollEffect){
        case 0:
            return 0;
            break;
        case 1:
            return (int)(fixedToFloat(sinLerp(degreesToAngle((timer%60)*6)), 12)*11);
            break;
        case 2:
            return (int)(fixedToFloat(sinLerp(degreesToAngle((timer%60)*6)), 12)*11);
            break;
        case 3:
            return 0;
            break;
    }

    return 0;
}

int CinematicFrame::addCalcY(int timer){
    if(time-timer < 60){
        switch(transition){
            case 0:
                break;
            case 1:
                break;
        }
    }
    switch(scrollEffect){
        case 0:
            return 0;
            break;
        case 1:
            return (int)(fixedToFloat(cosLerp(degreesToAngle((timer%60)*6)), 12)*8);
            break;
        case 2:
            return 0;
            break;
        case 3:
            return (int)(fixedToFloat(cosLerp(degreesToAngle((timer%60)*6)), 12)*8);
            break;
    }

    return 0;
}

CinematicFrame::~CinematicFrame(){
    destroy();
    unLoad();
}

Cinematic::Cinematic(std::string filename){
    std::ifstream file(filename);
    std::string readText;
    getline(file, readText);
    if(readText != "_CIN"){
        NF_Error(6000, "asd", 3);
    }
    getline(file, readText);
    while(readText != "\\"){
        std::string image = readText;
        getline(file, readText);
        int tim = stoi(readText);
        getline(file, readText);
        int scroll = stoi(readText);
        getline(file, readText);
        int trans = stoi(readText);
        frames.emplace_back(CinematicFrame(image, image+"name", tim, scroll, trans));
        getline(file, readText);
        getline(file, readText);
    }
}

void Cinematic::play(){
    mmLoad(MOD_INTRO);
    mmStart(MOD_INTRO, MM_PLAY_ONCE);
    for(auto frame : frames){
        frame.load();
        frame.create();
        while(timer < frame.time){
            NF_ScrollBg(0, 0, 128+frame.addCalcX(timer), 160+frame.addCalcY(timer));
            NF_SpriteOamSet(0);
            NF_SpriteOamSet(1);
            swiWaitForVBlank();
            oamUpdate(&oamMain);
            oamUpdate(&oamSub);
            timer++;
        }
        timer = 0;
        frame.destroy();
        frame.unLoad();
    }
    mmStop();
    mmUnload(MOD_INTRO);
}