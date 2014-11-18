//
//  AnalysisFactory.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/12/14.
//
//

#include "AnalysisFactory.h"

AnalysisFactory::AnalysisFactory()
{

}

AnalysisFactory::~AnalysisFactory()
{
    
}

void AnalysisFactory::analyze(APAudioFile* audio,
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
                if(data.name == audio->getName() && data.type == "fourier")
                    _fourierAnalysis = data;
            
            DFTAnalyzer _fourierAnalyzer;
            
            _fourierAnalyzer.init(N, overlap, t);
            _fourierAnalyzer.readAndAnalyse(audio->getAudioChannel(0), audio->getNumSamples());
            _fourierAnalyzer.calculateAmplitudes();
            _fourierAnalyzer.calculatePhases();
            _fourierAnalyzer.generatePeakMap();
            
            _fourierAnalysis.name = audio->getName();
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
            
        case YIN:
        {
            YINAnalyzer _yinAnalyzer;
            YINAnalysis _yinAnalysis;
            
            _yinAnalyzer.init(N);
            _yinAnalyzer.readAndAnalyse(audio->getAudioChannel(0), audio->getNumSamples());
            
            _yinAnalysis.name = audio->getName();
            _yinAnalysis.type = "yin";
            _yinAnalysis.N = N;
            _yinAnalysis.pitch = _yinAnalyzer.getResult();
            
            _yinResults.emplace_back(std::move(_yinAnalysis));
            
            _yinDataAvailable = true;
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
}

YINAnalysis& AnalysisFactory::getYinData(std::string file)
{
    for (auto& data: _yinResults)
    {
        if(data.name == file)
            return data;
    }
}

void AnalysisFactory::clear()
{
    _fourierResults.clear();
}