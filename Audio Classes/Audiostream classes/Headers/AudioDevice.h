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
#include <vector>

#include "AudioProcessor.h"
#include "portaudio.h"

class AudioDevice
{
public:
    AudioDevice();
    ~AudioDevice();
    
    void listDevices();
    
    void addCallback(AudioProcessor* audioProcessor_);
    void addCallback(std::function<void(float** input, float** output, long bufferSize)> callback);
    std::function<void(float** input, float** output, long bufferSize)> getLambda(){return callbackLambda;};
    
    void setSampleRate(long sampleRate);
    void setBufferSize(long bufferSize);
private:
    
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    
    long sampleRate = 44100;
    long bufferSize = 512;
    
    std::function<void(float** input, float** output, long bufferSize)> callbackLambda = nullptr;
    AudioProcessor* audioProcessor;
    
    std::vector<const PaDeviceInfo*> connectedHardware;
};

struct AppleAudioDevice
{
    AudioDevice device;
};

#endif /* defined(__GUI__AudioDevice__) */
