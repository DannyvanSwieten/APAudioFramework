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

std::vector<std::vector<float>> AnalysisFactory::analyze(ANALYSISMETHOD method,
                                                         ANALYSISRESULT result,
                                                         int N,
                                                         int overlap,
                                                         WindowType t)
{
    std::vector<std::vector<float>> analysisResult;
    
    switch (method)
    {
        case FOURIER:
        {
            _analyzer = std::make_unique<DFTAnalyzer>(N, overlap, t);
            break;
        }
            
        case WAVELET:
        {
            break;
        }
            
        case CONSTANTQ:
        {
            break;
        }
            
        default:
            break;
    }
    
    
    switch (result)
    {
        case AMPLITUDE:
        {
            _analyzer->calculateAmplitudes();
            analysisResult = _analyzer->getAmplitudes();
            break;
        }
            
        case PHASE:
        {
            _analyzer->calculatePhases();
            analysisResult = _analyzer->getPhases();
            break;
        }
            
        case PEAKS:
        {

            break;
        }
            
        default:
            break;
    }
    
    _analyzer.reset();
    return analysisResult;
}