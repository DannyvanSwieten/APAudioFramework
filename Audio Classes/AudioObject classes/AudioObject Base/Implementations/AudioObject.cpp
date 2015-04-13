//
//  AudioObject.cpp
//  AudioEnvironment
//
//  Created by Danny van Swieten on 2/26/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "AudioObject.h"

Inlet::Inlet(std::string name_, unsigned int maxConnections_)
{
    maxConnections = maxConnections_;
    name = name_;
}

void Inlet::connect(AudioObject *connection)
{
    connections.emplace_back(connection);
    input = true;
}

AudioObject::AudioObject()
{
    t = SAMPLE;
}

AudioObject::~AudioObject()
{
    
}

void AudioObject::createInlet(std::string name_, unsigned int maxConnections)
{
    auto inlet = std::make_unique<Inlet>(name_, maxConnections);
    inlets[name_] = std::move(inlet);
    numInlets = inlets.size();
}

void AudioObject::connect(std::string input, AudioObject *object)
{
    inlets[input]->connect(object);
}

void AudioObject::onPrepareToPlay(float samplerate_, float bufferSize_)
{
    samplerate = samplerate_;
    bufferSize = bufferSize_;
}

size_t AudioObject::getNumInlets()
{
    return inlets.size();
}

size_t AudioObject::getNumOutlets()
{
    return numOutlets;
}

void AudioObject::calculateSample()
{
    
}

void AudioObject::calculateBuffer()
{

}

float AudioObject::getOutput(unsigned long timeStamp_)
{
    timeStamp = timeStamp_;
    
    if(timeStamp > prevTimeStamp)
    {
        for(auto& inlet: inlets)
            for(auto& connection: inlet.second->connections)
                connection->getOutput(timeStamp_);
        
        calculateSample();
        prevTimeStamp = timeStamp;
        return output;
    }
    else
    {
        prevTimeStamp = timeStamp;
        return output;
    }
}
