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
    auto it = find_if(_timeLine.begin(), _timeLine.end(),[&](APAEvent event) {return event.getTimeStamp() >= timeStamp;});
    _timeLine.emplace(it ,APAEvent(getGurrentTime() + timeStamp, function, repeat));
}

void APAScheduler::update(unsigned long timeStamp)
{
    _currentTime = timeStamp;
    
    while(!_timeLine.empty() && _timeLine.front().getTimeStamp() <= _currentTime)
    {
        _timeLine.front().process();
        _timeLine.erase(_timeLine.begin());
    }
}