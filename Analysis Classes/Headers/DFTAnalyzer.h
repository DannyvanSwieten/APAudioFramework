//
//  DFTAnalyzer.h
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__DFTAnalyzer__
#define __DFT__DFTAnalyzer__

#include "SpectralAnalyzer.h"
#include "DFT.h"
#include <iostream>

class DFTAnalyzer: public SpectralAnalyzer
{
public:
    
    DFTAnalyzer(unsigned int N, unsigned int overlap, WindowType t);
    ~DFTAnalyzer();
    
    void readAndAnalyse(const float* input, long numberOfSamples) override;
    void calculateAmplitudes()override;
    void calculatePhases()override;
    void calculateInstantFrequencies()override;
    void calculateSpectralFlux();
    std::vector<std::vector<float>> getAmplitudes(){return _amplitudes;};
    std::vector<std::vector<float>> getPhases(){return _phases;};
    std::vector<std::vector<float>> getFrequenies(){return _trueFrequencies;};
    std::vector<float> getSpectralFlux(){return _spectralFlux;};
private:
    
    class DFT dft;
    float _freqPerBin = 0;
    std::vector<std::complex<float>> _buffer;
    std::vector<std::vector<std::complex<float>>> _analysisResult;
    std::vector<std::vector<float>> _phases;
    std::vector<std::vector<float>> _amplitudes;
    std::vector<std::vector<float>> _trueFrequencies;
    std::vector<float> _spectralFlux;
};

#endif /* defined(__DFT__DFTAnalyzer__) */
