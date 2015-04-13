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

void Gain::calculateSample()
{
    gain = inlets["Gain"]->connections[0]->output;
    input = 0;
    for(auto& connection: inlets["Input"]->connections)
    {
        input += connection->output;
    }
    
    float outputSample = 0;
    outputSample = input * gain;
}

void Gain::calculateBuffer()
{
    
}