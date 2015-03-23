//
//  APAScheduler.h
//  APASchedulerTest
//
//  Created by Danny van Swieten on 10-07-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APASchedulerTest__APAScheduler__
#define __APASchedulerTest__APAScheduler__

#include <vector>
#include <algorithm>
#include <mutex>
#include "Event.h"

class Scheduler
{
public:
    Scheduler();
    ~Scheduler();
    
    using EventFuntion = std::function<void()>;
    
    void addEvent(long long int timeStamp, EventFuntion function, bool repeat);
    void update(long long int timeStamp);
    void play();
    void stop();
    
    inline unsigned long int getGurrentTime(){return currentTime;};
    
private:
    
    std::mutex mutex;
    std::vector<Event> timeLine;
    long long int currentTime;
};

#endif /* defined(__APASchedulerTest__APAScheduler__) */
