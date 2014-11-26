//
//  TestAudioProcessor.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "TestAudioProcessor.h"

TestAudioProcessor::TestAudioProcessor()
{
    
}

TestAudioProcessor::~TestAudioProcessor()
{
    
}

void TestAudioProcessor::render(float *input, float *output, unsigned long numSamples)
{
    for (auto i = 0; i < 512; i++)
    {
        *output++ = (rand() % 3) - 1;
        *output++ = (rand() % 3) - 1;
    }
}