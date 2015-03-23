//
//  APAScheduler.cpp
//  APASchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Scheduler.h"

Scheduler::Scheduler()
{
    currentTime = 0;
}

Scheduler::~Scheduler()
{
    
}

void Scheduler::play()
{

}

void Scheduler::addEvent(long long int timeStamp, EventFuntion function, bool repeat)
{
    auto it = find_if(timeLine.begin(), timeLine.end(),[&](Event event) {return event.getTimeStamp() >= timeStamp;});
    
    timeLine.emplace(it, Event(getGurrentTime() + timeStamp, function, repeat));
}

void Scheduler::update(long long timeStamp)
{
    currentTime = timeStamp;
    
    mutex.lock();
    while(!timeLine.empty() && timeLine.front().getTimeStamp() <= currentTime)
    {
        timeLine.front().process();
        timeLine.erase(timeLine.begin());
    }
    
    mutex.unlock();
}