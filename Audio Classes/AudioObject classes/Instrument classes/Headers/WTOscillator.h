//
//  WTOscillator.h
//  SpeechSynthesizer
//
//  Created by Danny van Swieten on 12/16/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __SpeechSynthesizer__WTOscillator__
#define __SpeechSynthesizer__WTOscillator__

#include <vector>
#include <cmath>
class WTOscillator
{
public:
    
    enum WAVEFORM
    {
        SINE,
        TRIANGLE,
        SAW,
        PULSE
    };
    
    WTOscillator(WAVEFORM waveform, int size);
    void calculateSpeed(float freq, float sampleRate);
    float tick();
    
private:
    
    int size = 0;
    float speed = 0;
    float frequency = 0;
    float frac = 0;
    float index = 0;
    unsigned int floorIndex = 0;
    unsigned int nextIndex = 0;
    std::vector<float> table;
};

#endif /* defined(__SpeechSynthesizer__WTOscillator__) */
