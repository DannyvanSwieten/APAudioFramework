//
//  Voice.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/8/15.
//
//

#ifndef __SmartSampler__Voice__
#define __SmartSampler__Voice__

#include "Envelope.h"

class APAudioSource;

namespace APAudio
{
    class Voice
    {
    public:
        Voice() = default;
        Voice(std::string ID);
        virtual ~Voice();
        
        float play();
        
        void setSource(APAudioSource* src);
        Envelope* getEnvelope();
        virtual void start();
        virtual void stop();
        bool isPlaying();
        std::string ID;
        
        int playingNumber = 0;
    private:
        
        Envelope env;
        APAudioSource* source;
        bool playing = false;
    };
}

#endif /* defined(__SmartSampler__Voice__) */
