//
//  GainObject.cpp
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#include "GainObject.h"

GainObject::GainObject(APAudio::Mainframe& mf_): APAudio::AudioObject(mf_)
{
    
}

void GainObject::setGain(float g)
{
    gain = g;
}

void GainObject::calculateBuffer()
{
    if(inputList.size() && gain > 0.0)
    {
        for(auto& input: inputList)
        {
            float* inputBuffer = input->outputBuffer.data();
            for(auto i = 0; i < getBufferSize(); i++)
            {
                outputBuffer[i] = inputBuffer[i] * gain;
            }
        }
    }
    else
        memset(outputBuffer.data(), 0, sizeof(float) * getBufferSize());
}