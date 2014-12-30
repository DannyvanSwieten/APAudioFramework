//
//  WaveletAnalyzer.cpp
//  FrameworkMaintenance
//
//  Created by Danny van Swieten on 12/11/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "WaveletAnalyzer.h"

namespace APAudio
{
    namespace Analysis
    {
        WaveletAnalysis::WaveletAnalysis(int f0, int fmax)
        {
            period = 44100 / f0;
            numFilters = fmax / f0;
            envelopes.resize(numFilters);
            
            for(auto i = 1; i < numFilters; i++)
            {
                wavelets.emplace_back(Wavelet(period / i, HANNING));
            }
        }
        
        WaveletAnalysis::~WaveletAnalysis()
        {
            
        }
        
        void WaveletAnalysis::analyze(APAudio::Audio::AudioFile& file)
        {
            for (auto& wavelet: wavelets)
            {
                auto result = wavelet * file.getAudioVector(0);
                results.emplace_back(result);
            }
        }
        
        void WaveletAnalysis::createEnvelope(int index)
        {
            float x1 = 0;
            float x2 = 0;
            float amp = 0;
            for(auto i = 0; i < results[index].size(); i++)
            {
                x2 = results[index][i];
                float xDiff = x2 - x1;
                float inc = (xDiff / (float)period) / (float)index;
                for(auto j = 1; j < period / (index+1); j++)
                {
                    envelopes[index].emplace_back(amp);
                    amp+= inc;
                }
                x1 = x2;
            }
        }
        
        void WaveletAnalysis::createEnvelopes()
        {
            for(auto i = 0; i < numFilters-2; i++)
                createEnvelope(i);
        }
    }
}