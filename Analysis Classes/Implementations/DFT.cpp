//
//  DFT.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "DFT.h"

DFT::DFT()
{
    
}

DFT::~DFT()
{
    delete [] _window;
}

void DFT::init(unsigned int N, WindowType t)
{
    _N = N;
    _window = new float[N]();
    createWindow(t);
    _DFTBuffer.resize(_N);
    _twiddleFactors.resize(_N);
    _inverseTwiddleFactors.resize(_N);
    _DFTResult.resize(_N);
    
    for (auto k = 0; k < N; k++)
    {
        _twiddleFactors[k].resize(_N);
        _inverseTwiddleFactors[k].resize(_N);
    }
    
    calculateTwiddleFactors();
}

void DFT::createWindow(WindowType t)
{
    ::createWindow(t, _window, _N);
}

void DFT::calculateTwiddleFactors()
{
    for (auto k = 0; k < _N; k++)
    {
        for (auto n = 0; n < _N; n++)
        {
            _twiddleFactors[k][n] = std::complex<float>(cos(2*M_PI/_N * k * n), -sin(2*M_PI/_N * k * n));
            _inverseTwiddleFactors[k][n] = std::complex<float>(cos(2*M_PI/_N * k * n), sin(2*M_PI/_N * k * n));
        }
    }
}

void DFT::calculateDFT(float *input)
{
    for (auto n = 0; n < _N; n++)
    {
        _DFTBuffer[n].imag(0.0);
        _DFTBuffer[n].real(input[n] * _window[n]);
        _DFTResult[n] = std::complex<float>(0,0);
    }
    
    for (auto k = 0; k < _N; k++)
    {
        for (auto n = 0; n < _N; n++)
        {
            _DFTResult[k] += (_DFTBuffer[n] * _twiddleFactors[k][n]);
        }
    }
}

void DFT::calculateIDFT(float *input)
{
    for (auto k = 0; k < _N; k++)
    {
        for (auto n = 0; n < _N; n++)
        {
            input[n] += (1.0/_N) * std::complex<float>(_DFTResult[k] * _inverseTwiddleFactors[k][n]).real();
        }
    }
}