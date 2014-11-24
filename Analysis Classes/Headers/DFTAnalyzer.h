//
//  DFTAnalyzer.h
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__DFTAnalyzer__
#define __DFT__DFTAnalyzer__

#include "AudioAnalyzer.h"
#include "DFT.h"

namespace APAudio
{
    namespace Analysis
    {
        class DFTAnalyzer: public AudioAnalyzer
        {
        public:
            
            DFTAnalyzer() = default;
            DFTAnalyzer(unsigned int N, unsigned int overlap, WindowType t);
            ~DFTAnalyzer();
            
            void init(unsigned int N, unsigned int overlap, WindowType t);
            void readAndAnalyse(const float* input, long numberOfSamples) override final;
            void calculateAmplitudes()override final;
            void calculatePhases()override final;
            void calculateInstantFrequencies()override final;
            void calculatePitch()override final;
            void calculateSpectralFlux();
            void calculateLogSpectrum();
            void generatePeakMap();
            void searchStableSinusoids();
            void inverse();
            
            std::vector<std::vector<float>> getFrequenies(){return _trueFrequencies;};
            std::vector<float> getSpectralFlux(){return _spectralFlux;};
            std::vector<std::vector<int>> _getPeaks(){return _peakMaps;};
            
        private:
            
            DFT _dft;
            float _freqPerBin = 0;
            std::vector<std::complex<float>> _buffer;
            std::vector<std::vector<std::complex<float>>> _analysisResult;
            std::vector<std::vector<float>> _trueFrequencies;
            std::vector<float> _spectralFlux;
            std::vector<std::vector<int>> _peakMaps;
            
            std::vector<std::vector<float>> _resynthesisMatrix;
        };
    }
}

#endif /* defined(__DFT__DFTAnalyzer__) */
