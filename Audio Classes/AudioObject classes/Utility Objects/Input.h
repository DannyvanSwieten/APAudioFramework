//
//  Input.h
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#ifndef __DAW__Input__
#define __DAW__Input__

#include "AudioObject.h"

class Input: public AudioObject
{
public:
    Input();
    void listenToChannel(unsigned int channel);
    void calculateSample()override;
    void calculateBuffer()override;
    
private:
    
    float* inputBuffer = nullptr;
    unsigned int counter = 0;
    unsigned int channel;
};
#endif /* defined(__DAW__Input__) */
