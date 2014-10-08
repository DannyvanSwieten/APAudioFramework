//
//  APAudioSampleSound.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 13-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioSampleSound__
#define __APAudioEngine__APAudioSampleSound__

#include "APAudioSoundDescription.h"
#include "APAudioFile.h"
#include "../JuceLibraryCode/JuceHeader.h"

class APAudioSampleSound: public APAudioSoundDescription
{
public:
    
    APAudioSampleSound();
    virtual ~APAudioSampleSound();
    
    bool listensToNote(ControlValue note) override;
    bool listensToChannel(ControlValue channel) override;
    
private:
    
    APAudioFile* _audioFile;
};

#endif /* defined(__APAudioEngine__APAudioSampleSound__) */
