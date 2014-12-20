//
//  AudioDevice.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__AudioDevice__
#define __GUI__AudioDevice__

#include <iostream>
#include <functional>
#include <memory>

#include "AudioProcessor.h"
#include "portaudio.h"

class AudioDevice
{
public:
    AudioDevice();
    ~AudioDevice();
    
    void addCallback(AudioProcessor* audioProcessor_);
    void addCallback(std::function<void(float* input, float* output)> callback);
    std::function<void(float* input, float* output)> getLambda(){return callbackLambda;};
private:
    
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    
    unsigned int sampleRate;
    unsigned int bufferSize;
    
    std::function<void(float* input, float* output)> callbackLambda = nullptr;
    AudioProcessor* audioProcessor;
};

struct AppleAudioDevice
{
    AudioDevice device;
};

#endif /* defined(__GUI__AudioDevice__) */
