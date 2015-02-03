//
//  AudioSource.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/8/15.
//
//

#ifndef __SmartSampler__AudioSource__
#define __SmartSampler__AudioSource__

#include <string>
#include "Parameter.h"

namespace APAudio
{
    class AudioSourceDescription
    {
    public:
        AudioSourceDescription();
        AudioSourceDescription(std::string type, std::string info, int note, int velocity, int channel);
        virtual ~AudioSourceDescription();
        
        bool check(int note, int velocity, int channel);
        bool listensToNote(int note);
        bool listensToVelocity(int velocity);
        bool listensToChannel(int channel);
        
        bool isPlaying();
        
        std::string ID;
        std::string info;
        Parameter<int> note;
        Parameter<int> velocity;
        Parameter<int> channel;
        
    private:
        
    };
}

#endif /* defined(__SmartSampler__AudioSource__) */
