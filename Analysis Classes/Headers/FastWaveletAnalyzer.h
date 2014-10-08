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
#include "SpectralAnalyzer.h"

class FastWaveletAnalyzer: public SpectralAnalyzer
{
public:
    FastWaveletAnalyzer(unsigned int N, unsigned int overlap);
    ~FastWaveletAnalyzer();
    
private:
    
    FastWavelet _wavelet;
    void readAndAnalyse(const float* input, long numberOfSamples) override;
    void calculatePhases() override;
    void calculateAmplitudes() override;
    void calculateInstantFrequencies() override;
    
};

#endif /* defined(__DFT__FastWavelet__) */
