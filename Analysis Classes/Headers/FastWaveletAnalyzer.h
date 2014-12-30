//
//  FastWavelet.h
//  DFT
//
//  Created by Danny van Swieten on 9/22/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__FastWaveletAnalyzer__
#define __DFT__FastWaveletAnalyzer__

#include "FastWavelet.h"

class FastWaveletAnalyzer
{
public:
    FastWaveletAnalyzer();
    ~FastWaveletAnalyzer();
    void init(long N, long overlap);
    void readAndAnalyse(const float* input, long numberOfSamples);
    
private:
    
    FastWavelet _wavelet;
};

#endif /* defined(__DFT__FastWavelet__) */
