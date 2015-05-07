//
//  APAudioEnvelope.h
//  MTGSC
//
//  Created by Danny van Swieten on 20-05-14.
//
//

#ifndef __MTGSC__APAudioEnvelope__
#define __MTGSC__APAudioEnvelope__

#include "Object.h"

class Envelope
{
public:
    
    Envelope();
    double getAmplitude();
    void calculateMultiplier(double startLevel,
                             double endLevel,
                             long int time);
    
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
    double amplitude;
    double multiplier;
    long int currentSampleIndex;
    long int indexForNextState;
    double stateValues[EnvelopeState::NUMSTATES];
    
    const double minValue;
};

#endif /* defined(__MTGSC__APAudioEnvelope__) */
