//
//  APAEvent.cpp
//  APASchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAEvent.h"

APAEvent::APAEvent()
{
    _repeat = false;
}

APAEvent::APAEvent(unsigned long int timeStamp, EventFunction function, bool repeat)
{
    _repeat = repeat;
    _timeStamp = timeStamp;
    _function = function;
}

APAEvent::~APAEvent()
{
    
}

void APAEvent::process()
{
    _function();
}