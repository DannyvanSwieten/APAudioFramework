//
//  Osc.h
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#ifndef __DAW__Osc__
#define __DAW__Osc__

#include "AudioObject.h"

class Osc: public AudioObject
{
public:
    Osc();
    void calculateBuffer()override final;
    void calculateSample()override final;
    void calculatePhi();
private:
    
    float frequency;
    float phi;
    float phase;
    
    float twoPi = 2 * M_PI;
};

#endif /* defined(__DAW__Osc__) */
