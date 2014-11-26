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
    
private:
    
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    
    std::function<void(float* input, float* output)> _callback = nullptr;
    AudioProcessor* audioProcessor;
};

#endif /* defined(__GUI__AudioDevice__) */
