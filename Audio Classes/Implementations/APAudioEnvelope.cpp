//
//  APAudioEnvelope.cpp
//  MTGSC
//
//  Created by Danny van Swieten on 20-05-14.
//
//

#include "APAudioEnvelope.h"

APAudioEnvelope::APAudioEnvelope():minValue(0.0001)
{
    stateValues[EnvelopeState::OFF]     = 0;
    stateValues[EnvelopeState::ATTACK]  = .001;
    stateValues[EnvelopeState::DECAY]   = 0.3;
    stateValues[EnvelopeState::SUSTAIN] = 1.;
    stateValues[EnvelopeState::RELEASE] = .5;
    
    amplitude   = 1;
    multiplier  = 0;
    currentSampleIndex  = 0;
    currentState = EnvelopeState::OFF;
}

ControlValue APAudioEnvelope::getAmplitude()
{
    if (currentState != EnvelopeState::OFF && currentState != EnvelopeState::SUSTAIN)
    {
        if (currentSampleIndex == indexForNextState)
        {
            EnvelopeState newState = static_cast<EnvelopeState>((currentState+1) % EnvelopeState::NUMSTATES);
            enterNextStage(newState);
        }
        amplitude *= multiplier;
        currentSampleIndex++;
    }
    return amplitude;
}

void APAudioEnvelope::calculateMultiplier(ControlValue startLevel,
                                          ControlValue endLevel,
                                          TimerValue time)
{
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (time);
}

void APAudioEnvelope::enterNextStage(APAudioEnvelope::EnvelopeState state)
{
    currentState = state;
    currentSampleIndex = 0;
    
    if(currentState == EnvelopeState::OFF || currentState == EnvelopeState::SUSTAIN)
    {
        indexForNextState = 0;
    }
    else
    {
        indexForNextState = stateValues[currentState] * 44100;
    }
    
    switch (state)
    {
        case EnvelopeState::OFF:
            amplitude = 0;
            multiplier = 1.0;
            break;
            
        case EnvelopeState::ATTACK:
            
            amplitude = minValue;
            calculateMultiplier(amplitude,
                                .5,
                                indexForNextState);
            break;
            
        case EnvelopeState::DECAY:
            amplitude = 0.5;
            calculateMultiplier(amplitude,
                                fmax(stateValues[EnvelopeState::SUSTAIN], minValue),
                                indexForNextState);
            break;
            
        case EnvelopeState::SUSTAIN:
            amplitude = stateValues[EnvelopeState::SUSTAIN];
            multiplier = 1.0;
            break;
            
        case EnvelopeState::RELEASE:
            calculateMultiplier(amplitude,
                                minValue,
                                indexForNextState);
            break;
            
        default:
            break;
    }
}