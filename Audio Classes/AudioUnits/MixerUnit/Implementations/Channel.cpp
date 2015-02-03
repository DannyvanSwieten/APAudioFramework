//
//  Channel.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 1/31/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "Channel.h"

Channel::Channel(int sampleRate_, int bufferSize_, unsigned int numInlets_, unsigned int numChannels_): AudioUnit(sampleRate_, bufferSize_, numInlets_ , numChannels_), inputObject(*this)
{
    auto leftChannel = std::make_unique<GainObject>(*this);
    leftChannel->connect(&inputObject);
    
    auto rightChannel = std::make_unique<GainObject>(*this);
    rightChannel->connect(&inputObject);
    
    channels.emplace_back(std::move(leftChannel));
    channels.emplace_back(std::move(rightChannel));
    
    setPanning(.25 * M_PI);
}

APAudio::AudioObject* Channel::getOutputObject(unsigned int channel)
{
    return channels[channel].get();
}

void Channel::setInputChannel(unsigned int channel)
{
    channelNumber = channel;
}

void Channel::enableInput()
{
    inputEnabled = true;
    inputObject.enableInput();
}

void Channel::disableInput()
{
    inputEnabled = false;
    inputObject.disableInput();
}

void Channel::feedInput(float **input, unsigned int numInputChannels, unsigned int numFrames)
{
    this->numInputChannels = numInputChannels;
    inputObject.feed(input[channelNumber]);
}

void Channel::setGain(float g)
{
    gain = g;
    
    channels[0]->setGain(leftGain * gain);
    channels[1]->setGain(rightGain * gain);
}

void Channel::setPanning(float angle)
{
    leftGain = sin(angle);
    rightGain = cos(angle);
    
    channels[0]->setGain(leftGain * gain);
    channels[1]->setGain(rightGain * gain);
}