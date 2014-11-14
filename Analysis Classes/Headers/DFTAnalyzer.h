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
#include "../JuceLibraryCode/JuceHeader.h"

class DFTAnalyzer: public SpectralAnalyzer
{
public:
    
    DFTAnalyzer(unsigned int N, unsigned int overlap, WindowType t);
    ~DFTAnalyzer();
    
    void init(unsigned int N, unsigned int overlap, WindowType t);
    void readAndAnalyse(const float* input, long numberOfSamples) override final;
    void calculateAmplitudes()override final;
    void calculatePhases()override final;
    void calculateInstantFrequencies()override final;
    void calculateSpectralFlux();
    void calculateLogSpectrum();
    void generatePeakMap();
    void searchStableSinusoids();
    void inverse();
    
    std::vector<std::vector<float>> getFrequenies(){return _trueFrequencies;};
    std::vector<float> getSpectralFlux(){return _spectralFlux;};
    std::vector<std::vector<int>> _getPeaks(){return _peakMaps;};
    AudioSampleBuffer _synthesisBuffer;
    
private:
    
    class DFT _dft;
    float _freqPerBin = 0;
    std::vector<std::complex<float>> _buffer;
    std::vector<std::vector<std::complex<float>>> _analysisResult;
    std::vector<std::vector<float>> _trueFrequencies;
    std::vector<float> _spectralFlux;
    std::vector<std::vector<int>> _peakMaps;
    
    std::vector<std::vector<float>> _resynthesisMatrix;
};

#endif /* defined(__DFT__DFTAnalyzer__) */
