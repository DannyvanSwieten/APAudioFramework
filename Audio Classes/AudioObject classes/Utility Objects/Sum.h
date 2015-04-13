//
//  Add.h
//  AudioEnvironment
//
//  Created by Danny van Swieten on 3/19/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __AudioEnvironment__Add__
#define __AudioEnvironment__Add__

#include <cmath>

#include "AudioObject.h"

class Sum: public AudioObject
{
public:
    Sum();
    void calculateSample()override;
    void calculateBuffer()override;
private:
    
    
};

#endif /* defined(__AudioEnvironment__Add__) */