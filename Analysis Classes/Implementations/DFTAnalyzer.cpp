//
//  DFTAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "DFTAnalyzer.h"
#include "YINAnalyzer.h"

DFTAnalyzer::DFTAnalyzer(): SpectralAnalyzer()
{

}

DFTAnalyzer::~DFTAnalyzer()
{
    
}

void DFTAnalyzer::init(unsigned int N, unsigned int overlap, WindowType t)
{
    setN(N);
    setOverlap(overlap);
    setHopsize(0);
    _dft.init(N, overlap, N, t);
}

void DFTAnalyzer::readAndAnalyse(const float *input, long numberOfSamples)
{
    unsigned long position = 0;
    float buffer[getWindowSize()];
    unsigned int windowSize = getWindowSize();
    unsigned int hopSize = getHopsize();
    
    _analysisResult.clear();
    
    while(numberOfSamples > 0)
    {
        for (auto i = 0; i < windowSize; i++)
        {
            if(position < numberOfSamples - 1)
                buffer[i] = input[position++];
            else
                buffer[i] = 0;
        }
        if (getOverlap() != 1)
            position -= (windowSize - hopSize);

        numberOfSamples -= hopSize;
        _dft.calculateDFT(buffer);
        
        _analysisResult.emplace_back(_dft.getResult());
    }
}

void DFTAnalyzer::calculateAmplitudes()
{
    _amplitudes.clear();
    for(auto i = 0; i < _analysisResult.size(); i++)
    {
        std::vector<float> amplitude;
        for(auto n = 0; n < _dft.getSize();n++)
        {
            amplitude.emplace_back( std::abs(_analysisResult[i][n])/((float)_dft.getSize()/2));
        }
        
        normalize(amplitude.data(), _dft.getSize());
        
        _amplitudes.emplace_back(amplitude);
    }
}

void DFTAnalyzer::calculatePhases()
{
    for(auto i = 0; i < _analysisResult.size(); i++)
    {
        std::vector<float> phase;
        for(auto n = 0; n < _dft.getSize();n++)
        {
            phase.emplace_back(std::arg(_analysisResult[i][n]));
        }
        _phases.emplace_back(phase);
    }
    
    for(auto i = 1; i < _analysisResult.size(); i++)
    {
        for(auto n = 0; n < _dft.getSize();n++)
        {
            while(_phases[i][n] - _phases[i-1][n] > M_PI)
                _phases[i][n] -= 2*M_PI;
            while(_phases[i][n] - _phases[i-1][n] < -M_PI)
                _phases[i][n] += 2*M_PI;
        }
    }
}

void DFTAnalyzer::calculateLogSpectrum()
{
    for(auto& amplitudes: _amplitudes)
    {
        std::vector<float> logAmp;
        for (auto i = 0; i < _dft.getSize(); i++)
        {
            amplitudes[i] = 20 * log10(amplitudes[i]);
        }
        normalize(amplitudes.data(), _dft.getSize());
    }
}

void DFTAnalyzer::calculateInstantFrequencies()
{
    for(auto i = 1; i < _phases.size(); i++)
    {
        std::vector<float> freq;
        for(auto j = 0; j < _dft.getSize(); j++)
        {
            float wrappedPhaseDetermination = phaseWrap((_phases[i][j] - _phases[i-1][j]) - (getHopsize() * (_freqPerBin) * j), M_PI);
            freq.emplace_back((_freqPerBin * j) + (wrappedPhaseDetermination/getHopsize()));
        }
        _trueFrequencies.emplace_back(freq);
    }
}

void DFTAnalyzer::calculateSpectralFlux()
{
    for (auto i = 0; i < _amplitudes.size()-2; i++)
    {
        float amplitude1 = 0;
        float amplitude2 = 0;
        float difference = 0;
        float result = 0;
        for (auto j = 0; j < _dft.getSize()/2; j++)
        {
            amplitude1 = _amplitudes[i][j];
            amplitude2 = _amplitudes[i + 1][j];
            difference = amplitude2 - amplitude1;
            
            if(difference > 0)
                result += difference;
            else
                result += 0;
        }
        
        _spectralFlux.emplace_back(result);
    }
    
    normalize(_spectralFlux.data(), _dft.getSize());
}