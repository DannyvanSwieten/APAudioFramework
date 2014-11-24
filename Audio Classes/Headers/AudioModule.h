//
//  APAudioModule.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioModule__
#define __APAudioEngine__APAudioModule__

#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>

namespace APAudio
{
    namespace Audio
    {

        using Sample        = float;
        using SampleBuffer  = float*;
        using ControlValue  = double;
        using TimerValue     = long long;
        using UInt          = unsigned int;

        class AudioModule;
        class Parameter;

        class Mainframe
        {
        public:
            
            Mainframe(Sample sr, TimerValue bs);
            virtual ~Mainframe();
            void addModule(AudioModule* module);
            
            inline ControlValue getSampleRate(){return sampleRate;};
            inline TimerValue   getBufferSize(){return bufferSize;};
            
        private:
            std::vector<AudioModule*> modules;
            ControlValue    sampleRate;
            TimerValue      bufferSize;
        };

        class AudioModule
        {
        public:
            
            AudioModule(Mainframe* mf);
            virtual ~AudioModule();
            virtual void calculateBuffer();
            
            void setID(std::string ID);
            inline std::string getID(){return ID;};
            
            Sample returnOutputSample(TimerValue index);
            
            void   connect(AudioModule* module);
            
            inline Sample getSampleRate(){return sampleRate;};
            inline TimerValue getBufferSize(){return bufferSize;};
            
            std::vector<Sample>outputBuffer;
            std::vector<AudioModule*> inputList;
            std::vector<Parameter*> parameters;
            
        private:
            
            TimerValue  bufferSize;
            TimerValue  prevIndex;
            Sample      sampleRate;
            Sample      outputSample;
            
            std::vector<Sample>inputBuffer;
            
            std::string ID;
        };
    }
}



#endif /* defined(__APAudioEngine__APAudioModule__) */
