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
#include "APAEvent.h"

class APAScheduler
{
public:
    APAScheduler();
    ~APAScheduler();
    
    using EventFuntion = std::function<void()>;
    
    void addEvent(unsigned long int timeStamp, EventFuntion function, bool repeat);
    void update(unsigned long int timeStamp);
    void play();
    void stop();
    
    inline unsigned long int getGurrentTime(){return _currentTime;};
    
private:
    
    std::vector<APAEvent> _timeLine;
    unsigned long int _currentTime;
};

#endif /* defined(__APASchedulerTest__APAScheduler__) */
