//
//  APAEvent.h
//  APASchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APASchedulerTest__APAEvent__
#define __APASchedulerTest__APAEvent__

#include <functional>

using EventFunction = std::function<void()>;

class Event
{
public:
    Event();
    Event(unsigned long int timeStamp, EventFunction function, bool repeat);
    ~Event();
    
    inline unsigned long int getTimeStamp(){return _timeStamp;};
    inline unsigned long int getOffset(){return _offset;};
    inline EventFunction getFunction(){return _function;};
    inline bool getRepeat(){return _repeat;};

    void process();
    
private:
    
    EventFunction _function;
    unsigned long int _timeStamp;
    bool _repeat;
    unsigned long int _offset;
};

#endif /* defined(__APASchedulerTest__APAEvent__) */
