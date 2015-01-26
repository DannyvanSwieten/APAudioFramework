//
//  Voice.cpp
//  SmartSampler
//
//  Created by Danny van Swieten on 1/8/15.
//
//

#include "Voice.h"
#include "AudioSource.h"

namespace APAudio
{
    Voice::Voice(std::string ID)
    {
        this->ID = ID;
    }
    
    Voice::~Voice()
    {
        
    }
    
    void Voice::setSource(APAudioSource *src)
    {
        source = src;
    }
    
    Envelope* Voice::getEnvelope()
    {
        return &env;
    }

    bool Voice::isPlaying()
    {
        return playing;
    }

    void Voice::start()
    {
        env.enterNextStage(Envelope::Envelope::ATTACK);
        playing = true;
    }

    void Voice::stop()
    {
        playing = false;
        delete source;
        source = nullptr;
    }
    
    float Voice::play()
    {
        if(env.getCurrentState() == Envelope::EnvelopeState::OFF)
        {
            stop();
            return 0;
        }
        
        return source->play() * env.getAmplitude();
    }
}