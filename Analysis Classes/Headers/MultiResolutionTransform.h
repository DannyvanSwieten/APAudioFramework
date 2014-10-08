//
//  MultiResolutionTransform.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/1/14.
//
//

#ifndef __FPTAnalyzer__MultiResolutionTransform__
#define __FPTAnalyzer__MultiResolutionTransform__

#include "WaveletTransform.h"
#include "SpectralAnalyzer.h"

class MultiResolutionTransform: public SpectralAnalyzer
{
public:
    MultiResolutionTransform(unsigned int N, unsigned int overlap);
    ~MultiResolutionTransform();
    
private:
    
    void readAndAnalyse(const float* input, long numberOfSamples) override;
    void calculatePhases() override;
    void calculateAmplitudes() override;
    void calculateInstantFrequencies() override;
    
    WaveletTransform _waveletTransform;
};

#endif /* defined(__FPTAnalyzer__MultiResolutionTransform__) */
