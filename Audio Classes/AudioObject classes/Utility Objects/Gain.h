//
//  Gain.h
//  AudioEnvironment
//
//  Created by Danny van Swieten on 3/19/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __AudioEnvironment__Gain__
#define __AudioEnvironment__Gain__

#include "AudioObject.h"

class Gain: public AudioObject
{
public:
    Gain();
    void setGain(float gain_);
    void calculateSample()override;
    void calculateBuffer()override;
    
private:
    
    float gain;
};

#endif /* defined(__AudioEnvironment__Gain__) */
