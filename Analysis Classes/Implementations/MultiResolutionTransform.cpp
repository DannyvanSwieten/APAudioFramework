//
//  MultiResolutionTransform.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#include "MultiResolutionTransform.h"

MultiResolutionTransform::MultiResolutionTransform(unsigned int N, unsigned int overlap): SpectralAnalyzer(N, overlap)
{
    _waveletTransform.init(N);
}

MultiResolutionTransform::~MultiResolutionTransform()
{

}

void MultiResolutionTransform::calculateAmplitudes()
{
    
}

void MultiResolutionTransform::calculatePhases()
{
    
}

void MultiResolutionTransform::calculateInstantFrequencies()
{
    
}

void MultiResolutionTransform::readAndAnalyse(const float *input, long numberOfSamples)
{
    unsigned long position = 0;
    unsigned int windowSize = getWindowSize();
    float buffer[windowSize];
    unsigned int hopSize = getHopsise();
    
    while(numberOfSamples > 0)
    {
        for (auto i = 0; i < windowSize; i++)
        {
            if(position < numberOfSamples)
                buffer[i] = input[position++];
            else
                buffer[i] = 0;
        }
        if (getOverlap() != 1)
            position -= (windowSize - hopSize);
        
        _waveletTransform.process(buffer, windowSize);
        
        numberOfSamples -= hopSize;
    }
}