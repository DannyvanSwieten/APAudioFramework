//
//  AudioDevice.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include <iostream>
#include <functional>
#include <memory>
#include <vector>

#define IOS

#include "AudioProcessor.h"

#ifndef IOS
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
#else

#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <AVFoundation/AVFoundation.h>
#include "Utility.h"

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
    
    std::vector<float> floatBuffer;
    std::vector<float> floatBuffer2;
    float** buffer;
private:
    
    AudioStreamBasicDescription stereoStreamFormat;
    AudioComponentDescription ioUnitDescription;
    AudioComponentDescription mixerUnitDescription;
    AudioComponentInstance audioUnit;
    AURenderCallbackStruct inputCallbackStruct;
    
    bool playing;
    bool interruptedDuringPlayback;
    float sampleRate = 44100;
    float bufferSize = 512;
    
    std::function<void(float** input, float** output, long bufferSize)> callbackLambda = nullptr;
    AudioProcessor* audioProcessor;
};

#endif

