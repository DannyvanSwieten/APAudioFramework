//
//  WaveletTransform.h
//  DFT
//
//  Created by Danny van Swieten on 9/24/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__WaveletTransform__
#define __DFT__WaveletTransform__

#include "Utility.h"
#include <complex>
#include <vector>
#include <iostream>

class WaveletTransform
{
public:
    
    WaveletTransform();
    void init(int N);
    void process(float* input, int i);
    
private:
    void calculateTwiddleFactors();
    std::vector<std::vector<float>> _result;
    std::vector<std::vector<float>> _phase;
    int _N = 0;
    std::vector<int> _periodSizes;
    std::vector<std::complex<float>> _inputBuffer;
    std::vector<std::vector<std::complex<float>>> _twiddleFactors;
    float* _window = nullptr;
};

#endif /* defined(__DFT__WaveletTransform__) */
