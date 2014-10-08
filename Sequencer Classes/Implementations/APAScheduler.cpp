//
//  APAScheduler.cpp
//  APASchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAScheduler.h"

APAScheduler::APAScheduler()
{
    _currentTime = 0;
}

APAScheduler::~APAScheduler()
{
    
}

void APAScheduler::play()
{

}

void APAScheduler::addEvent(unsigned long int timeStamp, EventFuntion function, bool repeat)
{
    _timeLine.push_back(APAEvent(getGurrentTime() + timeStamp, function, repeat));
}

void APAScheduler::update(unsigned long timeStamp)
{
    _currentTime = timeStamp;
    for(auto& event : _timeLine)
    {
        if(timeStamp >= event.getTimeStamp())
        {
            event.process();
            _timeLine.pop_back();
        }
    }
}