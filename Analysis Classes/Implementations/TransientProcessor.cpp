//
//  TransientProcessor.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/20/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "TransientProcessor.h"

void TransientProcessor::processTransients(SpectralAnalyzer* analyzer, AnalysisType t)
{
    DFTAnalyzer* thisAnalyzer = (DFTAnalyzer*)analyzer;
    switch (t)
    {
        case DFT:
            processDFT(thisAnalyzer);
            break;
            
        default:
            break;
    }
}

void TransientProcessor::processDFT(DFTAnalyzer* analyzer)
{
    float phaseDiff     = 0;
    float phaseDiff2    = 0;
    float detector      = 0;
    
    for (auto i = 0; i < analyzer->getPhases().size()-2; i++)
    {
        phaseDiff   = 0;
        phaseDiff2  = 0;
        detector    = 0;
        
        for (auto j = 0; j < analyzer->getWindowSize(); j++)
        {
            phaseDiff   = analyzer->getPhases()[i+1][j] - analyzer->getPhases()[i][j];
            phaseDiff2 = analyzer->getPhases()[i+2][j] - analyzer->getPhases()[i+1][j];
            detector += fabs(phaseDiff2) - fabs(phaseDiff);
        }
        
        _result.emplace_back(fabs(detector));
    }
}