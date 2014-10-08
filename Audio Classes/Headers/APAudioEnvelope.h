//
//  APAudioEnvelope.h
//  MTGSC
//
//  Created by Danny van Swieten on 20-05-14.
//
//

#ifndef __MTGSC__APAudioEnvelope__
#define __MTGSC__APAudioEnvelope__

#include "APAudioModule.h"

class APAudioEnvelope
{
public:
    
    APAudioEnvelope();
    ControlValue getAmplitude();
    void calculateMultiplier(ControlValue startLevel,
                             ControlValue endLevel,
                             TimerValue time);
    
    enum EnvelopeState
    {
        OFF,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE,
        NUMSTATES
    };
    
    void enterNextStage(EnvelopeState state);
    inline EnvelopeState getCurrentState() const {return currentState;};
    
private:
    
    EnvelopeState currentState;
    ControlValue amplitude;
    ControlValue multiplier;
    TimerValue currentSampleIndex;
    TimerValue indexForNextState;
    ControlValue stateValues[EnvelopeState::NUMSTATES];
    
    const ControlValue minValue;
};

#endif /* defined(__MTGSC__APAudioEnvelope__) */
