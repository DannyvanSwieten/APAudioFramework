//
//  APAudioModule.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioModule__
#define __APAudioEngine__APAudioModule__

#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
//#include "Functions.h"

#include "../JuceLibraryCode/JuceHeader.h"


using Sample        = float;
using SampleBuffer  = float*;
using ControlValue  = double;
using TimerValue     = long long;
using UInt          = unsigned int;

class APAudioModule;
class APAudioParameter;

class APAudioMainFrame
{
public:
    
    APAudioMainFrame(Sample sr, TimerValue bs);
    virtual ~APAudioMainFrame();
    void addModule(APAudioModule* module);
    
    inline ControlValue getSampleRate(){return sampleRate;};
    inline TimerValue   getBufferSize(){return bufferSize;};
    
private:
    std::vector<APAudioModule*> modules;
    ControlValue    sampleRate;
    TimerValue      bufferSize;
};

class APAudioModule
{
public:
    
    APAudioModule(APAudioMainFrame* mf);
    virtual ~APAudioModule();
    virtual void calculateBuffer();
    
    void setID(juce::String ID);
    inline juce::String getID(){return ID;};
    
    Sample returnOutputSample(TimerValue index);
    
    void   connect(APAudioModule* module);
    
    inline Sample getSampleRate(){return sampleRate;};
    inline TimerValue getBufferSize(){return bufferSize;};
    
    std::vector<Sample>outputBuffer;
    std::vector<APAudioModule*> inputList;
    std::vector<APAudioParameter*> parameters;
    
private:
    
    TimerValue  bufferSize;
    TimerValue  prevIndex;
    Sample      sampleRate;
    Sample      outputSample;
    
    std::vector<Sample>inputBuffer;
    
    juce::String ID;
};



#endif /* defined(__APAudioEngine__APAudioModule__) */
