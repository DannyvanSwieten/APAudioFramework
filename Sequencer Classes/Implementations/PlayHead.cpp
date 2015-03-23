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
    sampleRate = 44100;
    
    samplesPerMinute = sampleRate * 60;
    samplesPerBeat = samplesPerMinute / beatsPerMinute;
    samplesPerBar = samplesPerBeat * numerator;
}

void PlayHead::setSampleRate(int sr)
{
    sampleRate = sr;
    
}

void PlayHead::setTempo(int bpm)
{
    beatsPerMinute = bpm;
}

void PlayHead::transport()
{
    if(playing)
    {
        samplePosition++;
        
        if (samplePosition % samplesPerBeat == 0){ beats++; std::cout<<"Bar: "<<bars<<" Beat: "<<beats<<"/"<<denominator<<std::endl; }
        if(beats == numerator) {beats = 0; bars++;}
        
    }
    
    if(paused || stopped)
    {
        
    }
}

void PlayHead::play()
{
    playing = true;
    paused = false;
    stopped = false;
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
    samplePosition = 0;
    milliSeconds = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
}