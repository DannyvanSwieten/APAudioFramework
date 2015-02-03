//
//  GainObject.h
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__GainObject__
#define __VSTHost__GainObject__

#include "AudioObject.h"

class GainObject: public APAudio::AudioObject
{
public:
    GainObject(APAudio::Mainframe& mf_);
    void calculateBuffer()override;
    
    void setGain(float g);
    
private:
    
    float gain = 1.0;
};

#endif /* defined(__VSTHost__GainObject__) */
