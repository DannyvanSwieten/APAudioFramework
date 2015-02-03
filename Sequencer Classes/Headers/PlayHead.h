//
//  PlayHead.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/30/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__PlayHead__
#define __VSTHost__PlayHead__

#include <thread>
#include <iostream>

class PlayHead
{
public:
    PlayHead();
    
    void transport();
    void reset();
    void play();
    void pause();
    void stop();
    
    long long counter = 0;
    
    long long milliSeconds = 0;
    long long seconds = 0;
    long long minutes = 0;
    long long hours = 0;
    
    bool playing = false;
    bool paused = false;
    bool stopped = true;
    
    std::thread playThread;
    
};

#endif /* defined(__VSTHost__PlayHead__) */
