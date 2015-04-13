//
//  Envelope.cpp
//  MTGSC
//
//  Created by Danny van Swieten on 20-05-14.
//
//

#include "Envelope.h"
Envelope::Envelope():minValue(0.0001)
{
    stateValues[EnvelopeState::OFF]     = 0;
    stateValues[EnvelopeState::ATTACK]  = 0.0;
    stateValues[EnvelopeState::DECAY]   = 0.3;
    stateValues[EnvelopeState::SUSTAIN] = 1.0;
    stateValues[EnvelopeState::RELEASE] = 1.0;
    
    amplitude   = 1;
    multiplier  = 0;
    currentSampleIndex  = 0;
    currentState = EnvelopeState::OFF;
}

double Envelope::getAmplitude()
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

void Envelope::calculateMultiplier(double startLevel,
                                          double endLevel,
                                          long int time)
{
    multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (time);
}

void Envelope::enterNextStage(Envelope::EnvelopeState state)
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