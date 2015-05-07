//
//  Input.h
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#ifndef __DAW__Input__
#define __DAW__Input__

#include "Object.h"
class DawAudioProcessor;
class Input: public AudioObject<float>
{
public:
    Input(DawAudioProcessor* processor_);
    void listenToChannel(unsigned int channel);
    void process()override;
    
private:
    
    DawAudioProcessor* processor;
    float* inputBuffer = nullptr;
    unsigned int counter = 0;
    unsigned int channel;
};
#endif /* defined(__DAW__Input__) */
