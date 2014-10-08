//
//  APAudioSequencer.cpp
//  APA
//
//  Created by Danny van Swieten on 17-07-14.
//
//

#include "APAudioSequencer.h"

APAudioSequencer::APAudioSequencer(APAScheduler* scheduler)
{
    _scheduler = scheduler;
}

void APAudioSequencer::update(unsigned int time)
{
    for(auto& event : _events)
    {
        if (event.getTimeStamp() <=  time)
        {
            _scheduler->addEvent(0, event.getFunction(), false);
        }
    }
}

void APAudioSequencer::addEvent(unsigned long int timeStamp, EventFunction function)
{
    _events.emplace_back(APAEvent(timeStamp, function, false));
}

void APAudioSequencer::play()
{
    
}

void APAudioSequencer::stop()
{
    
}

void APAudioSequencer::pause()
{
    
}