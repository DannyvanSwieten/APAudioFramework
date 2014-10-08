//
//  APAudioModule.
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioModule.h"

APAudioMainFrame::APAudioMainFrame(Sample sr, TimerValue bs)
{
    bufferSize = bs;
    sampleRate = sr;
}

APAudioMainFrame::~APAudioMainFrame()
{
    
}

void APAudioMainFrame::addModule(APAudioModule *module)
{
    modules.emplace_back(module);
}

//--------------------Module-------------------------------
APAudioModule::APAudioModule(APAudioMainFrame* mf)
{
    mf->addModule(this);
    bufferSize = mf->getBufferSize();
    sampleRate = mf->getSampleRate();
    
    outputBuffer.resize(bufferSize);
    
    prevIndex = 0;
}

void APAudioModule::setID(juce::String ID)
{
    this->ID = ID;
}

APAudioModule::~APAudioModule()
{
    
}

void APAudioModule::connect(APAudioModule *module)
{
    inputList.emplace_back(module);
}

Sample APAudioModule::returnOutputSample(TimerValue index)
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

void APAudioModule::calculateBuffer()
{
    
}

