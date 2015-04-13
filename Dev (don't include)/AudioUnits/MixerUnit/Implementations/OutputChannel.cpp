//
//  OutputChannel.cpp
//  DAW
//
//  Created by Danny van Swieten on 2/1/15.
//
//

#include "OutputChannel.h"

OutputChannel::OutputChannel(unsigned int numInlets_, unsigned int numChannels_): Unit(numInlets_, numChannels_)
{
    auto leftChannel = std::make_unique<Gain>(*this);
    auto rightChannel = std::make_unique<Gain>(*this);
    
    leftChannel->connect("Main" ,inlets[0].summer.get());
    rightChannel->connect("Main", inlets[0].summer.get());
    
    channels.emplace_back(std::move(leftChannel));
    channels.emplace_back(std::move(rightChannel));
    
    setPanning(.25 * M_PI);
}

AudioObject* OutputChannel::getOutputObjectForChannel(unsigned int channel)
{
    return channels[channel].get();
}

void OutputChannel::setPanning(float angle)
{
    leftGain = sin(angle);
    rightGain = cos(angle);
    
    channels[0]->setGain(leftGain * gain);
    channels[1]->setGain(rightGain * gain);
}

void OutputChannel::setGain(float g)
{
    gain = g;
    
    channels[0]->setGain(leftGain * gain);
    channels[1]->setGain(rightGain * gain);
}