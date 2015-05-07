//
//  AudioObject.h
//  AudioEnvironment
//
//  Created by Danny van Swieten on 2/26/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __AudioEnvironment__AudioObject__
#define __AudioEnvironment__AudioObject__

#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include "Parameter.h"

class Inlet;

class AudioObject
{
public:
    AudioObject();
    virtual ~AudioObject();

    void connect(unsigned int inlet, AudioObject* object);
    void connect(std::string name, AudioObject* block);
    
    void update();

    void onPrepareToPlay(float sampleRate, float bufferSize);
    float getBufferSize(){return bufferSize;};
    float getSamplerate(){return samplerate;};
    virtual void calculateBuffer();
    virtual std::string getName();
    virtual void updateArguments(std::vector<std::string> args);
    std::vector<std::string>& getArguments(){return arguments;};
    
    float getOutput(unsigned long timeStamp_, unsigned long bufferIndex);
    
    float output = 0;
    std::vector<float> outputBuffer;
    float input = 0;
    
    size_t getNumInlets();
    size_t getNumOutlets();
    
    void createInlet(std::string name, unsigned int maxConnections);
    
    std::map<std::string, std::unique_ptr<Inlet>> inlets;
    std::map<std::string, std::unique_ptr<AudioObject>> outlets;
    std::vector<Parameter<float>> parameters;
    
    enum PROCESSINGTYPE
    {
        BUFFER,
        SAMPLE
    };

private:
    
    std::vector<std::string> arguments;
    
    unsigned long prevBufferIndex = 0;
    
    size_t numInlets = 0;
    size_t numOutlets = 0;
    
    unsigned long timeStamp = 0;
    unsigned long prevTimeStamp = 0;
    
    float samplerate = 0;
    float bufferSize = 0;
    
    unsigned long counter = 0;
    
    PROCESSINGTYPE t;
};

class Inlet
{
public:
    Inlet(std::string name, unsigned int maxConnections);
    void connect(AudioObject* connection);
    std::vector<AudioObject*> connections;
    bool hasInput(){return input;};
    
private:
    
    bool input = false;
    unsigned int maxConnections;
    std::string name;
};

#endif /* defined(__AudioEnvironment__AudioObject__) */
