//
//  APAudioVoice.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioVoice__
#define __APAudioEngine__APAudioVoice__

#include "APAudioSoundDescription.h"
#include "APAudioSampleSound.h"
#include "APAudioModule.h"
#include "APAudioEnvelope.h"

class APAudioVoice
{
public:
    
    APAudioVoice();
    virtual ~APAudioVoice();
    
    virtual void renderNextBlock (SampleBuffer outputBuffer,
                                  int startSample,
                                  int numSamples,
                                  UInt channel) = 0;
    
    virtual void stopVoice() = 0;
    
    virtual bool canPlaySound(APAudioSoundDescription* sound) = 0;
    
    void setSound(APAudioSoundDescription* sound);
    void releaseVoice();
    void setIsPlaying(bool playing);
    void setPitch(ControlValue pitch);
    void setID(UInt ID);
    inline UInt getID(){return voiceID;};
    
    inline bool getIsPlaying(){return isPlaying;};
    inline ControlValue getPitch(){return pitch;};
    inline APAudioSoundDescription* getSound(){return sound;};
    
    inline APAudioEnvelope* getEnvelope()const{return envelope;};
    
    virtual void reset() = 0;
    
private:
    
    friend class APAudioVoiceManager;
    
    APAudioSoundDescription* sound;
    APAudioEnvelope* envelope;
    
    UInt idx;
    UInt voiceID;
    ControlValue pitch;
    bool isPlaying;
    UInt voiceNr;
    
};
#endif /* defined(__APAudioEngine__APAudioVoice__) */
