//
//  FastWavelet.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/22/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "FastWaveletAnalyzer.h"

FastWaveletAnalyzer::FastWaveletAnalyzer(unsigned int N, unsigned int overlap): SpectralAnalyzer(N, overlap)
{
    
}

FastWaveletAnalyzer::~FastWaveletAnalyzer()
{
    
}

void FastWaveletAnalyzer::calculateAmplitudes()
{
    
}

void FastWaveletAnalyzer::calculatePhases()
{
    
}

void FastWaveletAnalyzer::calculateInstantFrequencies()
{
    
}

void FastWaveletAnalyzer::readAndAnalyse(const float *input, long numberOfSamples)
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
        
        _wavelet.process(buffer, windowSize, 1);
        
        numberOfSamples -= hopSize;
    }
}