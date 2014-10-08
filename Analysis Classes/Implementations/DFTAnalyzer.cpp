//
//  DFTAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "DFTAnalyzer.h"
#include "YINAnalyzer.h"

DFTAnalyzer::DFTAnalyzer(unsigned int N, unsigned int overlap, WindowType t): SpectralAnalyzer(N, overlap)
{
    dft.init(N, t);
    _freqPerBin = 2*M_PI / N;
}

DFTAnalyzer::~DFTAnalyzer()
{
    
}

void DFTAnalyzer::readAndAnalyse(const float *input, long numberOfSamples)
{
    unsigned long position = 0;
    float buffer[getWindowSize()];
    unsigned int windowSize = getWindowSize();
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

        numberOfSamples -= hopSize;
        dft.calculateDFT(buffer);
        
        _analysisResult.emplace_back(dft.getResult());
    }
}

void DFTAnalyzer::calculateAmplitudes()
{
    for(auto i = 0; i < _analysisResult.size(); i++)
    {
        std::vector<float> amplitude;
        for(auto n = 0; n < dft.getSize();n++)
        {
            amplitude.emplace_back( std::abs(_analysisResult[i][n])/((float)dft.getSize()/2));
        }
        
        normalize(amplitude.data(), dft.getSize());
        
        _amplitudes.emplace_back(amplitude);
    }
}

void DFTAnalyzer::calculatePhases()
{
    for(auto i = 0; i < _analysisResult.size(); i++)
    {
        std::vector<float> phase;
        for(auto n = 0; n < dft.getSize();n++)
        {
            phase.emplace_back(std::arg(_analysisResult[i][n]));
        }
        _phases.emplace_back(phase);
    }
    
    for(auto i = 1; i < _analysisResult.size(); i++)
    {
        for(auto n = 0; n < dft.getSize();n++)
        {
            while(_phases[i][n] - _phases[i-1][n] > M_PI)
                _phases[i][n] -= 2*M_PI;
            while(_phases[i][n] - _phases[i-1][n] < -M_PI)
                _phases[i][n] += 2*M_PI;
        }
    }
}

void DFTAnalyzer::calculateInstantFrequencies()
{
    for(auto i = 1; i < _phases.size(); i++)
    {
        std::vector<float> freq;
        for(auto j = 0; j < dft.getSize(); j++)
        {
            float wrappedPhaseDetermination = phaseWrap((_phases[i][j] - _phases[i-1][j]) - (getHopsise() * (_freqPerBin) * j), M_PI);
            freq.emplace_back((_freqPerBin * j) + (wrappedPhaseDetermination/getHopsise()));
        }
        _trueFrequencies.emplace_back(freq);
    }
}

void DFTAnalyzer::calculateSpectralFlux()
{
    for (auto i = 0; i < _amplitudes.size()-2; i++)
    {
        float amplitude = 0;
        float amplitude2 = 0;
        float amplitude3 = 0;
        for (auto j = 0; j < dft.getSize()/2; j++)
        {
            amplitude += _amplitudes[i][j];
            amplitude2 += _amplitudes[i+1][j];
            amplitude3 += _amplitudes[i+2][j];
        }
        float difference1 = amplitude2 - amplitude;
        float difference2 = amplitude3 = amplitude2;
        
        _spectralFlux.emplace_back(difference2 - difference1);
    }
    
    normalize(_spectralFlux.data(), dft.getSize());
}