//
//  FrequencyAnalyzer.h
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#ifndef __APAAnalyzer__FrequencyAnalyzer__
#define __APAAnalyzer__FrequencyAnalyzer__
#include "YIN.h"
#include "AudioFileManager.h"
#include "AudioAnalyzer.h"

namespace APAudio
{
    namespace Analysis
    {
        class YINAnalyzer: AudioAnalyzer
        {
        public:
            
            YINAnalyzer();
            void readAndAnalyse(const float* input, long numberOfSamples) override final;
            void calculateAmplitudes()override final;
            void calculatePhases()override final;
            void calculateInstantFrequencies()override final;
            void calculatePitch() override final;
            std::vector<float> getResult(){return _result;};
            void init(int N);
            
        private:
            
            YIN yin;
            float _prevSample = 0;
            int _downsample = 1;
            int _N;
            std::vector<float> _result;
        };
    }
}

#endif /* defined(__APAAnalyzer__FrequencyAnalyzer__) */
