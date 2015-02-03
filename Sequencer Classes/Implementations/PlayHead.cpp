//
//  PlayHead.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 1/30/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "PlayHead.h"

PlayHead::PlayHead()
{
    playThread = std::thread(&PlayHead::transport, this);
    playThread.detach();
}

void PlayHead::transport()
{
    while(playing)
    {
        counter++;
        
        milliSeconds = counter % 1000;
        seconds = (counter / 1000) % 60;
        minutes = (counter / (60 * 1000)) % 60;
        hours = (counter / (1000 * 60 * 60)) % 24;
        
        std::cout<<hours<<" "<<minutes<<" "<<seconds<<" "<<milliSeconds<<std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    while(paused)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void PlayHead::play()
{
    playing = true;
    paused = false;
    stopped = false;
    playThread = std::thread(&PlayHead::transport, this);
    playThread.detach();
}

void PlayHead::pause()
{
    paused = true;
    playing = false;
}

void PlayHead::stop()
{
    stopped = true;
    playing = false;
    paused = false;
    reset();
}

void PlayHead::reset()
{
    counter = 0;
    milliSeconds = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
}