//
//  Channel.h
//  VSTHost
//
//  Created by Danny van Swieten on 1/31/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__Channel__
#define __VSTHost__Channel__

#include "AudioUnit.h"
#include "MidiInput.h"
#include "InputObject.h"
#include "GainObject.h"

class Channel: public AudioUnit
{
public:
    Channel(int sampleRate_, int bufferSize_, unsigned int numInlets_, unsigned int numChannels_);
    
    APAudio::AudioObject* getOutputObject(unsigned int channel)override final;
    void setGain(float g);
    void setPanning(float angle);
    void feedInput(float **input, unsigned int numChannels, unsigned int numFrames);
    
    float getCurrentAmplitude(){return currentAmplitude;};
    void enableInput();
    void disableInput();
    
    int getNumChannels(){return numInputChannels;};
    void setInputChannel(unsigned int channel);
    bool isInputEnabled(){return inputEnabled;};
    
private:
    
    InputObject inputObject;
    std::vector<std::unique_ptr<GainObject>> channels;
    
    unsigned int channelNumber = 0;
    
    void setLeftGain(float lg);
    void setRightGain(float rg);
    
    float gain = 1.0;
    float leftGain = sin(M_PI / 4);
    float rightGain = cos(M_PI / 4);
    
    float** input;
    bool inputEnabled = false;
    float currentAmplitude;
    
    int numInputChannels = 0;
};

#endif /* defined(__VSTHost__Channel__) */
