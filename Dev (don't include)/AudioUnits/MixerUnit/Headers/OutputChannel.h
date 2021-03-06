//
//  OutputChannel.h
//  DAW
//
//  Created by Danny van Swieten on 2/1/15.
//
//

#ifndef __DAW__OutputChannel__
#define __DAW__OutputChannel__

#include "Unit.h"
#include "Gain.h"

class OutputChannel: public Unit
{
public:
    OutputChannel(unsigned int numInlets_, unsigned int numChannels_);
    ~OutputChannel(){};
    AudioObject* getOutputObjectForChannel(unsigned int channel)override final;
    void setGain(float g);
    void setPanning(float angle);
    
private:
    
    std::vector<std::unique_ptr<Gain>> channels;
    
    unsigned int channelNumber = 0;
    
    void setLeftGain(float lg);
    void setRightGain(float rg);
    
    float gain = 1.0;
    float leftGain = sin(0.1*M_PI);
    float rightGain = cos(0.1*M_PI);
};

#endif /* defined(__DAW__OutputChannel__) */
