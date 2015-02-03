//
//  SummerObject.h
//  DAW
//
//  Created by Danny van Swieten on 2/2/15.
//
//

#ifndef __DAW__SummerObject__
#define __DAW__SummerObject__

#include "AudioObject.h"

class SummerObject: public APAudio::AudioObject
{
public:
    SummerObject(APAudio::Mainframe& mf_);
    void calculateBuffer()override;
    
private:
    
    float gain = 1.0;
};

#endif /* defined(__DAW__SummerObject__) */
