//
//  PlayHead.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/30/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__PlayHead__
#define __VSTHost__PlayHead__

#include <iostream>

class PlayHead
{
public:
    PlayHead();
    
    void setSampleRate(int sr);
    void setTempo(int bpm);
    
    void transport();
    void reset();
    void play();
    void pause();
    void stop();
    
    long long samplePosition = 0;
    long bars = 1;
    
    long beatsPerMinute = 120;
    long samplesPerMinute = 0;
    long samplesPerBeat = 0;
    long samplesPerBar = 0;
    
    int beats = 0;
    
    int numerator = 4;
    int denominator = 4;
    
    
    long long milliSeconds = 0;
    long long seconds = 0;
    long long minutes = 0;
    long long hours = 0;
    
    bool playing = false;
    bool paused = false;
    bool stopped = true;
    
    long sampleRate = 0;
    
};

#endif /* defined(__VSTHost__PlayHead__) */
