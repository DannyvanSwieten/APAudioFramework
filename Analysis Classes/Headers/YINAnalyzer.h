//
//  FrequencyAnalyzer.h
//  APAAnalyzer
//
//  Created by Danny van Swieten on 10/2/14.
//
//

#include "YIN.h"
#include "AudioFileManager.h"

namespace APAudio
{
    namespace Analysis
    {
        class YINAnalyzer
        {
        public:
            
            YINAnalyzer();
            void init(int N);
            void readAndAnalyse(const float* input, long numberOfSamples);
            std::vector<float> getResult(){return _result;};
            
        private:
            
            YIN yin;
            void calculatePitch();
            float _prevSample = 0;
            int _downsample = 1;
            int _N;
            std::vector<float> _result;
        };
    }
}
