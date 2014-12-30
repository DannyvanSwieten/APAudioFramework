//
//  Module.
//  Engine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "AudioModule.h"

namespace APAudio
{
    namespace Audio
    {

        Mainframe::Mainframe(Sample sr, TimerValue bs)
        {
            bufferSize = bs;
            sampleRate = sr;
        }

        Mainframe::~Mainframe()
        {
            
        }

        void Mainframe::addModule(AudioModule *module)
        {
            modules.emplace_back(module);
        }

        //--------------------Module-------------------------------
        AudioModule::AudioModule(Mainframe* mf)
        {
            mf->addModule(this);
            bufferSize = mf->getBufferSize();
            sampleRate = mf->getSampleRate();
            
            outputBuffer.resize(bufferSize);
            
            prevIndex = 0;
        }

        void AudioModule::setID(std::string ID)
        {
            this->ID = ID;
        }

        AudioModule::~AudioModule()
        {
            
        }

        void AudioModule::connect(AudioModule *module)
        {
            inputList.emplace_back(module);
        }

        Sample AudioModule::returnOutputSample(TimerValue index)
        {
            if (index < prevIndex)
            {
                outputSample = outputBuffer[bufferSize - prevIndex + index];
            }
            else
            {
                if (inputList.size() != 0)
                {
                    for (auto& input : inputList)
                    {
                        if (input != NULL)
                        {
                            for (auto i = 0; i < bufferSize; i++)
                            {
                                input->outputBuffer[i] = input->returnOutputSample(prevIndex + i);
                            }
                        }
                    }
                }
                prevIndex = index + bufferSize;
                calculateBuffer();
                outputSample = outputBuffer[bufferSize - prevIndex + index];
            }
            return outputSample;
        };

        void AudioModule::calculateBuffer()
        {
            
        }
    }
}

