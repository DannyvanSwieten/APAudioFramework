//
//  APAudioSamplerVoice.cpp
//  APAudioEngine
//
//  Created by Danny van Swieten on 08-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioSamplerVoice.h"

APAudioSamplerVoice::APAudioSamplerVoice()
{
    idx = 0;
    floorIdx = 0;
    frac = 0;
}

bool APAudioSamplerVoice::canPlaySound(APAudioSoundDescription *sound)
{
    if (sound == dynamic_cast<APAudioSampleSound*>(sound))
        return true;
    else
        return true;
}

void APAudioSamplerVoice::reset()
{

}

void APAudioSamplerVoice::stopVoice()
{
    
}

void APAudioSamplerVoice::renderNextBlock (SampleBuffer outputBuffer,
                                           int startSample,
                                           int numSamples,
                                           UInt channel)
{
//    APAudioSampleSound* sound = (APAudioSampleSound*)getSound();
//    
//    for (auto i = 0; i < numSamples; i++)
//    {
//        ControlValue amplitude = getEnvelope()->getAmplitude();
//        
//        if((amplitude == 0.0 && getIsPlaying()) || (idx > sound->getLength()/2))
//        {
//            idx = 0;
//            setIsPlaying(false);
//        }
//        Sample outputSample = sound->data.getSample(channel, floorIdx) +
//        frac*(sound->data.getSample(channel, floorIdx + 1) - sound->data.getSample(channel, floorIdx));
//        
//        outputBuffer[i] += outputSample * amplitude;
//        
//        idx += getPitch();
//        floorIdx = (int)idx;
//        frac = idx - floorIdx;
//    }
}