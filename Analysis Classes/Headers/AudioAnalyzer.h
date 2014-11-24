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
#include <vector>
#include "Utility.h"

namespace APAudio
{
    namespace Analysis
    {
        class AudioAnalyzer
        {
        public:
            
            AudioAnalyzer();
            virtual ~AudioAnalyzer() = 0;
            virtual void readAndAnalyse(const float* input, long numberOfSamples) = 0;
            virtual void calculatePhases() = 0;
            virtual void calculateAmplitudes() = 0;
            virtual void calculateInstantFrequencies() = 0;
            virtual void calculatePitch() = 0;
            
            void setHopsize(int hopSize);
            void setN(int N);
            void setOverlap(int N);
            
            int getHopsize(){return _ra;};
            int getWindowSize(){return _N;};
            int getOverlap(){return _overlap;};
            
            std::vector<std::vector<float>>& getAmplitudes(){return _amplitudes;};
            std::vector<std::vector<float>>& getPhases(){return _phases;};
            std::vector<float>& getPitch(){return _pitch;};
            
        private:
            
            std::vector<std::vector<float>> _amplitudes;
            std::vector<std::vector<float>> _phases;
            std::vector<float> _pitch;
            
            int _ra = 0;
            int _N = 0;
            int _overlap = 0;
        };
    }
}

#endif /* defined(__DFT__SpectralAnalyzer__) */
