//
//  AnalysisFactory.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/12/14.
//
//

#include "AnalysisFactory.h"

namespace APAudio
{
    namespace Analysis
    {
        AnalysisFactory::AnalysisFactory()
        {

        }

        AnalysisFactory::~AnalysisFactory()
        {
            
        }

        void AnalysisFactory::analyze(APAudio::Audio::AudioFile audio,
                                      ANALYSISMETHOD method,
                                      int N,
                                      int overlap,
                                      WindowType t)
        {
            switch (method)
            {
                case FOURIER:
                {
                    SpectralAnalysis _fourierAnalysis;
                    
                    for(auto& data: _fourierResults)
                        if(data.name == audio.getName() && data.type == "fourier")
                            _fourierAnalysis = data;
                    
                    DFTAnalyzer _fourierAnalyzer;
                    
                    _fourierAnalyzer.init(N, overlap, t);
                    _fourierAnalyzer.readAndAnalyse(audio.getAudioChannel(0), audio.getNumSamples());
                    _fourierAnalyzer.calculateAmplitudes();
                    _fourierAnalyzer.calculatePhases();
                    _fourierAnalyzer.generatePeakMap();
                    
                    _fourierAnalysis.name = audio.getName();
                    _fourierAnalysis.type = "Fourier";
                    _fourierAnalysis.N = N;
                    _fourierAnalysis.overlap = overlap;
                    _fourierAnalysis.amplitudes = _fourierAnalyzer.getAmplitudes();
                    _fourierAnalysis.peakMap = _fourierAnalyzer._getPeaks();
                    _fourierAnalysis.phases = _fourierAnalyzer.getPhases();
                    
                    _fourierResults.emplace_back(std::move(_fourierAnalysis));
                    _fourierDataAvailable = true;
                    break;
                }
                    
                default:
                    break;
            }
        }

        SpectralAnalysis& AnalysisFactory::getFourierData(std::string file)
        {
            for (auto& data: _fourierResults)
            {
                if(data.name == file)
                    return data;
            }
            return _emptySpec;
        }

        YINAnalysis& AnalysisFactory::getYinData(std::string file)
        {
            for (auto& data: _yinResults)
            {
                if(data.name == file)
                    return data;
            }
            return _emptyYin;
        }

        void AnalysisFactory::clear()
        {
            _fourierResults.clear();
        }
        
        SpectralAnalysis AnalysisFactory::transpose(std::string file, float ratio)
        {
            auto result = getFourierData(file);
            float index = 0;
            for(auto& row: result.amplitudes)
            {
                std::vector<float> newRow;
                newRow.resize(result.N);
                
                for(auto i = 0; i < result.N; i++)
                {
                    newRow[(int)index] += row[i];
                    index += ratio;
                }
                row = newRow;
            }
            return result;
        }
    }
}