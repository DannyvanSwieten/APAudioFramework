//
//  Sampler.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef __FuChair__Sampler__
#define __FuChair__Sampler__

#include "AudioFileManager.h"
#include "SoundDescription.h"
#include "SamplerVoice.h"
#include "AudioModule.h"

namespace APAudio
{
    namespace Audio
    {
        class Sampler: public AudioModule
        {
        public:
            Sampler(Mainframe* mainFrame ,AudioFileManager* fileManager);
            ~Sampler();
            void onNoteOn(int noteOn, float velocity, int channel, bool repeat);
            void onNoteOn(std::string file, float velocity, int channel, bool repeat);
            void onNoteOff(std::string file);
            SamplerVoice* findFreeVoice();
            void renderBlock(SampleBuffer output);
            void loadFile(std::string fileToLoad, int noteToListenTo, int channelToListenTo);
            void calculateBuffer()override;
            void setSpeed(float speed);
            void setSpeed(std::string file,float speed);
            void setVoiceAmplitude(int voice, float amp);
            void clearVoices(){_activeVoices.clear();};
            
        private:
            
            std::vector<SamplerVoice* > _activeVoices;
            std::vector<SoundDescription> _fileDescriptions;
            AudioFileManager* _fileManager;
            int _numVoicesActive = 0;
        };
    }
}

#endif /* defined(__FuChair__Sampler__) */
