//
//  Gain.cpp
//  AudioEnvironment
//
//  Created by Danny van Swieten on 3/19/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "Gain.h"

Gain::Gain(): AudioObject()
{
    createInlet("Input", 1);
    createInlet("Gain", 1);
}

void Gain::setGain(float gain_)
{
    gain = gain_;
}

void Gain::calculateBuffer()
{
    for(auto sample = 0; sample < getBufferSize(); sample++)
    {
        gain = inlets["Gain"]->connections[0]->outputBuffer[sample];
        outputBuffer[sample] += inlets["Input"]->connections[0]->outputBuffer[sample] * gain;
    }
}