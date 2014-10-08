//
//  WaveletTransform.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/24/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "WaveletTransform.h"

WaveletTransform::WaveletTransform()
{
    
}

void WaveletTransform::init(int N)
{
    _N = N;
    _window = new float[_N];
    float minFreq = 44100.0 / (float)_N;
    _result.resize(log2(N));
    _phase.resize(log2(N));
    for (auto i = 0; i < log2(_N); i++)
    {
        _periodSizes.emplace_back(44100.0 / minFreq);
        minFreq *= 2;
    }
    
    createWindow(HANNING, _window, _N);
    calculateTwiddleFactors();
}

void WaveletTransform::calculateTwiddleFactors()
{
    int stepSize = 1;
    for (auto k = 0; k < log2(_N); k++)
    {
        std::vector<std::complex<float>> _twiddleVector;
        for (auto n = 0; n < _periodSizes[k]; n++)
        {
            std::complex<float> twiddle = std::complex<float>(cos(2*M_PI/_periodSizes[k] * n) ,
                                                                -sin(2*M_PI/_periodSizes[k] * n));
            
            _twiddleVector.emplace_back(twiddle);
        }
        _twiddleFactors.emplace_back(_twiddleVector);
        stepSize*=2;
    }
}

void WaveletTransform::process(float *input, int i)
{
    for (auto j = 0; j < _N; j++)
    {
        _inputBuffer.emplace_back(std::complex<float>(input[j] * _window[j], 0.0));
    }
    
    int periodSize = _periodSizes[i];
    int index = 0;
    for(auto period = 0; period < _N / _periodSizes[i]; period++)
    {
        std::complex<float> result;
        for (auto j = 0; j < periodSize; j++)
        {
            result += _twiddleFactors[i][j] * _inputBuffer[index++];
        }
        _result[i].emplace_back(std::abs(result) / periodSize);
        _phase[i].emplace_back(atan2(result.imag(), result.real()));
    }
    std::cout<<std::endl;
}