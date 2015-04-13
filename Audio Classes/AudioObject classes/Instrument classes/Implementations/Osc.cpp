//
//  Osc.cpp
//  DAW
//
//  Created by Danny van Swieten on 4/9/15.
//
//

#include "Osc.h"

Osc::Osc()
{
    createInlet("Frequency", 1);
}

void Osc::calculatePhi()
{
    phi = twoPi / getSamplerate() * frequency;
}

void Osc::calculateBuffer()
{
    
}

void Osc::calculateSample()
{
    frequency = 0;
    for(auto& connection: inlets["Frequency"]->connections)
        frequency += connection->output;
    
    calculatePhi();
    
    output = sin(phase);
    phase+=phi;
    
    while(phase > twoPi)
        phase-=twoPi;
}