//
//  AudioUnit.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "AudioUnit.h"

AudioUnit::AudioUnit(int sampleRate_, int bufferSize_, unsigned int numInlets_, unsigned int numChannels_): APAudio::Mainframe(sampleRate_, bufferSize_)
{
    numInlets = numInlets_;
    numChannels = numChannels_;
    
    inlets.resize(numInlets);
    
    // Create the inlets
    for (auto& inlet : inlets)
    {
        inlet = std::make_unique<Inlet>();
        inlet->mixers.resize(numChannels);
        for (auto& mixer : inlet->mixers)
            mixer = std::make_unique<SummerObject>(*this);
    }
}

void AudioUnit::connect(AudioUnit *unit, unsigned int inlet)
{
    if(inlet >= numInlets)
        return;
    if(unit->getNumChannels() != numChannels)
        return;
    
    inlets[inlet]->units.emplace_back(unit);
    
    for(auto channel = 0; channel < numChannels; channel++)
        inlets[inlet]->mixers[channel]->connect(unit->getOutputObject(channel));
    
    connections.emplace_back(unit);
}

void AudioUnit::disconnect(AudioUnit* unit, unsigned int inlet)
{
    if(inlet >= numInlets)
        return;
    
    auto& inletRef = *inlets[inlet];
    
    // See if the unit was connected
    auto it = find(begin(inletRef.units), end(inletRef.units), unit);
    if (it == end(inletRef.units))
        return;
    
    // Remove the unit
    inletRef.units.erase(it);
    
    // Disconnect from the mixer
    for (auto channel = 0; channel < numChannels; ++channel)
        inletRef.mixers[channel]->disconnect(unit->getOutputObject(channel));
    
    // let the connected unit know it is no longer connected to this unit. deliberately leave duplicates in case the same unit is connected to different inlets!
    for (auto it = unit->connections.begin(); it < unit->connections.end(); ++it)
        if (*it == this)
        {
            unit->connections.erase(it);
            break;
        }
}

unsigned int AudioUnit::getNumChannels()
{
    return numChannels;
}

unsigned int AudioUnit::getNumInlets()
{
    return numInlets;
}