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
#include "APAudioSoundDescription.h"
#include "APAudioSamplerVoice.h"
#include "APAudioModule.h"

class APAudioSampler: public APAudioModule
{
public:
    APAudioSampler(APAudioMainFrame* mainFrame ,APAudioFileManager* fileManager);
    ~APAudioSampler();
    void onNoteOn(int noteOn, float velocity, int channel, bool repeat);
    void onNoteOn(std::string file, float velocity, int channel, bool repeat);
    void onNoteOff(std::string file);
    APAudioSamplerVoice* findFreeVoice();
    void renderBlock(SampleBuffer output);
    void loadFile(std::string fileToLoad, int noteToListenTo, int channelToListenTo);
    void calculateBuffer()override;
    void setSpeed(float speed);
    void setSpeed(std::string file,float speed);
    void setVoiceAmplitude(int voice, float amp);
    void clearVoices(){_activeVoices.clear();};
    
private:
    
    std::vector<APAudioSamplerVoice* > _activeVoices;
    std::vector<APAudioSoundDescription> _fileDescriptions;
    APAudioFileManager* _fileManager;
    int _numVoicesActive = 0;
};

#endif /* defined(__FuChair__Sampler__) */
