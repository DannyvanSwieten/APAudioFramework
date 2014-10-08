//
//  APAudioSourceManager.h
//  APA
//
//  Created by Danny van Swieten on 13-07-14.
//
//

#ifndef __APA__APAudioSourceManager__
#define __APA__APAudioSourceManager__

#include "APAudioSampleSound.h"

class APAudioSourceManager
{
public:
    APAudioSourceManager();
    ~APAudioSourceManager();
    
    APAudioSoundDescription* loadFile();
    
private:
    
    AudioFormatManager formatManager;
    AudioFormatReader* formatReader = nullptr;
    std::vector<APAudioSoundDescription> sounds;
};

#endif /* defined(__APA__APAudioSourceManager__) */
