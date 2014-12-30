//
//  WaveletAnalyzer.h
//  FrameworkMaintenance
//
//  Created by Danny van Swieten on 12/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __FrameworkMaintenance__WaveletAnalyzer__
#define __FrameworkMaintenance__WaveletAnalyzer__

#include "Wavelet.h"
#include "AudioFile.h"
#include <iostream>

using namespace APAudio::Audio;

namespace APAudio
{
    namespace Analysis
    {
        class WaveletAnalysis
        {
        public:
            WaveletAnalysis(int f0, int fmax);
            ~WaveletAnalysis();
            
            void analyze(AudioFile& file);
            void createEnvelopes();
        private:
            
            void createEnvelope(int index);
            std::vector<std::vector<float>> results;
            std::vector<std::vector<float>> envelopes;
            std::vector<Wavelet> wavelets;
            int period = 0;
            int numFilters = 0;
        };
    }
}

#endif /* defined(__FrameworkMaintenance__WaveletAnalyzer__) */
