//
//  WTOscillator.cpp
//  SpeechSynthesizer
//
//  Created by Danny van Swieten on 12/16/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "WTOscillator.h"

WTOscillator::WTOscillator(WAVEFORM waveform, int size)
{
    this->size = size;
    table.resize(size);
    switch (waveform)
    {
        case SINE:
        {
            for(auto i = 0; i < size; i++)
                table[i] = sin(2*M_PI / size * i);
            
            break;
        }
            
        case SAW:
        {
            int inc = 1.0 / (float)size;
            float sample = 0;
            for(auto i = 0; i < size; i++)
            {
                table[i] = sample;
                sample += inc;
                
                if (i == size / 2)
                    sample -= 2;
            }
            break;
        }
            
        default:
            break;
    }
}

void WTOscillator::calculateSpeed(float freq, float sampleRate)
{
    float base = sampleRate / (float)size;
    speed = freq / base;
}

float WTOscillator::tick()
{
    float output;
    floorIndex = (int)index;
    nextIndex = floorIndex + 1;
    frac = index - floorIndex;
    
    output = table[floorIndex] + (frac * (table[nextIndex] - table[floorIndex]));
    
    index += speed;
    if(index > size)
        index-=size;
    
    return output;
}