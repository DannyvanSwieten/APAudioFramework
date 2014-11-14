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
        NUMMETHODS
    };
    
    enum ANALYSISRESULT
    {
        AMPLITUDE,
        PHASE,
        PEAKS,
        NUMRESULTS
    };
    
    std::vector<std::vector<float>> analyze(ANALYSISMETHOD method,
                                            ANALYSISRESULT result,
                                            int N,
                                            int overlap,
                                            WindowType t);
    
private:

    std::unique_ptr<SpectralAnalyzer> _analyzer;
};

#endif /* defined(__FPTAnalyzer__AnalysisFactory__) */
