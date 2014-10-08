//
//  APAudioVoiceManager.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioVoiceManager__
#define __APAudioEngine__APAudioVoiceManager__

#include "APAudioSamplerVoice.h"
#include "APAudioModule.h"

class APAudioVoiceManager: public APAudioModule
{
public:
    APAudioVoiceManager(APAudioMainFrame* mf, UInt channel);
    APAudioVoice* findFreeVoice(APAudioSoundDescription* soundDescription, ControlValue pitch);
    
    void noteOn(ControlValue pitch, ControlValue ID);
    void noteOff(UInt ID);
    void updatePitch(ControlValue pitch, ControlValue ID);
    
    void addSound(APAudioSoundDescription* s);
    
    void startVoice(APAudioVoice* voice, APAudioSoundDescription* sound, ControlValue pitch, ControlValue velocity);
    void addSamplerVoice();
    void destroyAllVoices();
    
    void calculateBuffer()override;
    
    UInt getActiveVoices();
    
    std::vector<APAudioVoice*> voices;
    std::vector<APAudioSoundDescription*> sounds;
    
private:

    UInt activeVoices;
    UInt channel;
};

#endif /* defined(__APAudioEngine__APAudioVoiceManager__) */
