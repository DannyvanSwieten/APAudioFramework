//
//  AnalysisFactory.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/12/14.
//
//

#ifndef __FPTAnalyzer__AnalysisFactory__
#define __FPTAnalyzer__AnalysisFactory__

#include "DFTAnalyzer.h"
#include "AudioFileManager.h"
#include "YINAnalyzer.h"

namespace APAudio
{
    namespace Analysis
    {
        class SpectralAnalysis
        {
        public:
            SpectralAnalysis(){};
            std::string name;
            std::string type;
            int N = 0;
            int overlap = 0;
            std::vector<std::vector<int>> peakMap;
            std::vector<std::vector<float>> amplitudes;
            std::vector<std::vector<float>> phases;
            std::vector<float> spectralFlux;
        };

        class YINAnalysis
        {
        public:
            
            YINAnalysis(){};
            std::string name;
            std::string type;
            int N;
            std::vector<float> pitch;
        };

        class AnalysisFactory
        {
        public:
            
            AnalysisFactory();
            ~AnalysisFactory();
            
            enum ANALYSISMETHOD
            {
                FOURIER,
                CONSTANTQ,
                WAVELET,
                YIN,
                NUMMETHODS
            };
            
            enum ANALYSISRESULT
            {
                AMPLITUDE,
                PHASE,
                PEAKS,
                PITCH,
                NUMRESULTS
            };
            
            void analyze(APAudio::Audio::AudioFile audio,
                         ANALYSISMETHOD method,
                         int N,
                         int overlap,
                         WindowType t);
            
            void clear();
            
            SpectralAnalysis& getFourierData(std::string file);
            YINAnalysis& getYinData(std::string file);
            bool fourierDataAvailable(){return _fourierDataAvailable;};
            bool yinDataAvailable(){return _yinDataAvailable;};
            
        private:
            
            bool _fourierDataAvailable = false;
            bool _yinDataAvailable = false;
            std::vector<SpectralAnalysis> _fourierResults;
            std::vector<YINAnalysis> _yinResults;
            
            YINAnalysis _emptyYin;
            SpectralAnalysis _emptySpec;
        };
    }
}

#endif /* defined(__FPTAnalyzer__AnalysisFactory__) */
