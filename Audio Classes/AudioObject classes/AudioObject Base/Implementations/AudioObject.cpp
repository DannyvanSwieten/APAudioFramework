//
//  Module.
//  Engine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "AudioObject.h"

namespace APAudio
{
    Mainframe::Mainframe()
    {
        
    }
    
    Mainframe::Mainframe(Sample sr, TimerValue bs)
    {
        bufferSize = bs;
        sampleRate = sr;
    }

    Mainframe::~Mainframe()
    {
        
    }
    
    void Mainframe::onPrepareToPlay(float sr, float bs)
    {
        setSampleRate(sr);
        setBufferSize(bs);
    }
    
    void Mainframe::setSampleRate(float sr)
    {
        sampleRate = sr;
        
        for(auto& module: modules)
            module->setSampleRate(sampleRate);
    }
    
    void Mainframe::setBufferSize(float bs)
    {
        bufferSize = bs;
        for(auto& module: modules)
            module->setBufferSize(bufferSize);
    }

    void Mainframe::addModule(AudioObject *module)
    {
        modules.emplace_back(module);
    }

    //--------------------Module-------------------------------
    
    AudioObject::AudioObject()
    {
        
    }
    
    AudioObject::AudioObject(Mainframe& mf)
    {
        mf.addModule(this);
        bufferSize = mf.getBufferSize();
        sampleRate = mf.getSampleRate();
        
        outputBuffer.resize(bufferSize);
        
        prevTime = 0;
    }

    void AudioObject::setID(std::string ID)
    {
        this->ID = ID;
    }

    AudioObject::~AudioObject()
    {
        
    }

    void AudioObject::connect(AudioObject *module)
    {
        inputList.emplace_back(module);
    }
    
    void AudioObject::disconnect(AudioObject* object)
    {
        auto it = inputList.begin();
        
        for(auto& input: inputList)
        {
            if(input == object)
                inputList.erase(it);
            
            it++;
        }
    }

    Sample AudioObject::returnOutputSample(TimerValue index)
    {
        if (index < prevTime)
        {
            outputSample = outputBuffer[bufferSize - prevTime + index];
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
                            input->outputBuffer[i] = input->returnOutputSample(prevTime + i);
                        }
                    }
                }
            }
            prevTime = index + bufferSize;

            calculateBuffer();
            outputSample = outputBuffer[bufferSize - prevTime + index];
        }
        return outputSample;
    };
    
    void AudioObject::calculateSample()
    {
        
    }

    void AudioObject::calculateBuffer()
    {
        
    }
}

