//
//  APAudioProcessorCPP.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioProcessorCPP__
#define __APAudioEngine__APAudioProcessorCPP__

#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Accelerate/Accelerate.h>

#include <vector>
#include <memory>
#include <iostream>
#include <cassert>
#include <functional>

#if defined __MAC_OS_X_VERSION_MAX_ALLOWED
#define USING_OSX
#include <CoreAudio/CoreAudio.h>
#else
#define USING_IOS
#include <AVFoundation/AVFoundation.h>
#endif

//! APAudioProcessor
/*!
 This is a singleton from which all the streams are played and all modules are managed and updated.
 */

typedef Float32     Sample;
typedef Float32*    SampleBuffer;
typedef Float64     ControlValue;
typedef UInt64      DiscreteTimeValue;

OSStatus outputRenderCallback(void *							inRefCon,
                              AudioUnitRenderActionFlags *      ioActionFlags,
                              const AudioTimeStamp *			inTimeStamp,
                              UInt32							inBusNumber,
                              UInt32							inNumberFrames,
                              AudioBufferList *                 ioData);

class APAudioProcessorCPP
{
public:
    
    APAudioProcessorCPP();
    virtual void process(UInt16 bufferSize, AudioBufferList* buffers) = 0;
    
    inline ControlValue getSampleRate(){return graphSampleRate;};
    inline UInt32       getBufferSize(){return sampleSize;};
    
    OSStatus    startProcessor();
    
private:
    
    OSStatus    setupAudioSession();
    OSStatus    setupProcessor();
    OSStatus    setupAudioUnits();
    
    OSStatus    setupStereoStreamFormat();
    OSStatus    setupMonoStreamFormat();
    
    void        printASBD(AudioStreamBasicDescription asbd);
    
    Float64     graphSampleRate;
    Float64     bufferSize;
    UInt16      sampleSize;
        
    UInt16      numInputChannels;
    UInt16      numOutputChannels;
        
    AUGraph     processingGraph;
        
    AUNode      IONode;
    AUNode      mixerNode;
    
    AudioUnit   IOUnit;
    AudioUnit   mixerUnit;
    
    AudioComponentDescription       IOComponentDescription;
    AudioComponentDescription       mixerComponentDescription;
        
    AudioStreamBasicDescription     stereoStreamDescription;
    AudioStreamBasicDescription     monoStreamDescription;
    bool                            audioIsRunning;
    
    std::vector<float> floats;
};

#endif /* defined(__APAudioEngine__APAudioProcessorCPP__) */
