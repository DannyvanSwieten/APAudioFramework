//
//  SpectralAnalyzer.h
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__SpectralAnalyzer__
#define __DFT__SpectralAnalyzer__

#include <math.h>

class SpectralAnalyzer
{
public:
    
    SpectralAnalyzer(unsigned int N, unsigned int overlap);
    virtual ~SpectralAnalyzer() = 0;
    virtual void readAndAnalyse(const float* input, long numberOfSamples) = 0;
    virtual void calculatePhases() = 0;
    virtual void calculateAmplitudes() = 0;
    virtual void calculateInstantFrequencies() = 0;
    
    unsigned int getHopsise(){return _ra;};
    unsigned int getWindowSize(){return _N;};
    unsigned int getOverlap(){return _overlap;};
    
private:
    
    unsigned int _ra = 0;
    unsigned int _N = 0;
    unsigned int _overlap = 0;
};

#endif /* defined(__DFT__SpectralAnalyzer__) */
