//
//  OutputChannel.cpp
//  DAW
//
//  Created by Danny van Swieten on 2/1/15.
//
//

#include "OutputChannel.h"

OutputChannel::OutputChannel(int sampleRate_, int bufferSize_, unsigned int numInlets_, unsigned int numChannels_): AudioUnit(sampleRate_, bufferSize_, numInlets_, numChannels_)
{
    auto leftChannel = std::make_unique<GainObject>(*this);
    auto rightChannel = std::make_unique<GainObject>(*this);
    
    leftChannel->connect(inlets[0]->mixers[0].get());
    rightChannel->connect(inlets[0]->mixers[1].get());
    
    channels.emplace_back(std::move(leftChannel));
    channels.emplace_back(std::move(rightChannel));
    
    setPanning(.25 * M_PI);
}

APAudio::AudioObject* OutputChannel::getOutputObject(unsigned int channel)
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