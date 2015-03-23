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
    using Sample        = float;
    using SampleBuffer  = float*;
    using ControlValue  = double;
    using TimerValue    = long long;
    using UInt          = unsigned int;

    class AudioObject;

    class Mainframe
    {
    public:
        
        Mainframe();
        Mainframe(Sample sr, TimerValue bs);
        virtual ~Mainframe();
        void addModule(AudioObject* module);
        
        inline ControlValue getSampleRate(){return sampleRate;};
        inline TimerValue   getBufferSize(){return bufferSize;};
        
        void onPrepareToPlay(float sr, float bs);
        
    private:
        
        void setSampleRate(float sr);
        void setBufferSize(float bs);
        
        std::vector<AudioObject*> modules;
        ControlValue    sampleRate;
        TimerValue      bufferSize;
    };

    class AudioObject
    {
    public:
        
        AudioObject();
        AudioObject(Mainframe& mf);
        virtual ~AudioObject();
        virtual void calculateBuffer();
        virtual void calculateSample();
        
        void setID(std::string ID);
        inline std::string getID(){return ID;};
        
        Sample returnOutputSample(TimerValue index);
        
        void   connect(AudioObject* object);
        void   disconnect(AudioObject* object);
        
        void setSampleRate(int sr){sampleRate = sr;}
        void setBufferSize(int bs){bufferSize = bs; outputBuffer.resize(bs); inputBuffer.resize(bs);}
        
        inline Sample getSampleRate(){return sampleRate;};
        inline TimerValue getBufferSize(){return bufferSize;};
        
        std::vector<Sample>outputBuffer;
        std::vector<AudioObject*> inputList;
        
        inline Sample output(TimerValue time)
        {
            if(time > prevTime)
            {
                for(auto& input: inputList)
                    input->calculateSample();
                
                calculateSample();
            }
            
            return outputSample;
        }
        
    private:
        
        TimerValue  bufferSize;
        TimerValue  prevTime;
        Sample      sampleRate;
        
        Sample      outputSample;
        
        std::vector<Sample>inputBuffer;
        
        std::string ID;
    };
}

#endif /* defined(__APAudioEngine__APAudioModule__) */
