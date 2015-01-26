//
//  VoiceManager.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/9/15.
//
//

#ifndef __SmartSampler__VoiceManager__
#define __SmartSampler__VoiceManager__

#include "AudioObject.h"
#include "AudioSourceManager.h"
#include "AudioFilePlayer.h"
#include "Voice.h"

namespace APAudio
{
    class VoiceManager: public AudioObject
    {
    public:
        VoiceManager();
        VoiceManager(Mainframe& mainFrame);
        VoiceManager(Mainframe& mainFrame, AudioSourceManager* manager);
        void calculateBuffer()override final;
        
        void noteOn(int note, int velocity, int channel);
        void noteOff(int note, int velocity, int channel);
        Voice* findFreeVoice();
        
    private:
        
        std::vector<std::unique_ptr<Voice>> voices;
        std::vector<std::unique_ptr<Voice>> extraVoices;
        AudioSourceManager* sourceManager = nullptr;
        int activeVoices = 0;
        int activeExtraVoices = 0;
    };
}

#endif /* defined(__SmartSampler__VoiceManager__) */
