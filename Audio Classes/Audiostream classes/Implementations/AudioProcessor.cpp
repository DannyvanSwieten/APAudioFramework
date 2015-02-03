//
//  AudioProcessor.cpp
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#include "AudioProcessor.h"

AudioProcessor::AudioProcessor()
{
    
}

AudioProcessor::~AudioProcessor()
{
    
}

void AudioProcessor::render(float** input, int numInputs, float** output, int numOutputs, unsigned long numSamples)
{
    
}

void AudioProcessor::setSampleRate(int sr)
{
    sampleRate = sr;
}

void AudioProcessor::setBufferSize(int bs)
{
    bufferSize = bs;
}

int AudioProcessor::getSampleRate()
{
    return sampleRate;
}

int AudioProcessor::getBufferSize()
{
    return bufferSize;
}