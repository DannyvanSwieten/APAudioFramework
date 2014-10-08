//
//  Sampler.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef __FuChair__Sampler__
#define __FuChair__Sampler__

#include "APAudioFileManager2.h"
#include "APSoundDescription.h"
#include "SamplerVoice.h"
#include "APAudioModule.h"

class Sampler: public APAudioModule
{
public:
    Sampler(APAudioMainFrame* mainFrame ,APAudioFileManager* fileManager);
    ~Sampler();
    void onNoteOn(int noteOn, float velocity, int channel);
    APSamplerVoice* findFreeVoice();
    void renderBlock(SampleBuffer output);
    void loadFile(std::string fileToLoad, int noteToListenTo, int channelToListenTo);
    void calculateBuffer()override;
    
private:
    
    std::vector<APSamplerVoice* > _activeVoices;
    std::vector<APSoundDescription> _fileDescriptions;
    APAudioFileManager* _fileManager;
};

#endif /* defined(__FuChair__Sampler__) */
