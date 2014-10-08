//
//  APAudioTransport.cpp
//  APA
//
//  Created by Danny van Swieten on 17-07-14.
//
//

#include "APAudioTransport.h"

APAudioTransport::APAudioTransport()
{
    _currentTime = 0;
}

void APAudioTransport::update(unsigned int time)
{
    _currentTime += time;
    for(auto& tracks : _tracks)
        tracks.update(_currentTime);
}

void APAudioTransport::addTrack(APAudioSequencer track)
{
    _tracks.emplace_back(track);
}

void APAudioTransport::play()
{
    
}

void APAudioTransport::pause()
{
    
}

void APAudioTransport::stop()
{
    
}

