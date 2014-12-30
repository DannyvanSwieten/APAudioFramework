//
//  Event.cpp
//  SchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Event.h"

Event::Event()
{
    _repeat = false;
}

Event::Event(unsigned long int timeStamp, EventFunction function, bool repeat)
{
    _repeat = repeat;
    _timeStamp = timeStamp;
    _function = function;
}

Event::~Event()
{
    
}

void Event::process()
{
    _function();
}