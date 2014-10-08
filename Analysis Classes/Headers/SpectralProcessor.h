//
//  SpectralProcessor.h
//  DFT
//
//  Created by Danny van Swieten on 9/19/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__SpectralProcessor__
#define __DFT__SpectralProcessor__

#include "SpectralAnalyzer.h"
#include <vector>

enum AnalysisType
{
    DFT
};

class SpectralProcessor
{
public:
    virtual ~SpectralProcessor() = 0;
    virtual void processTransients(SpectralAnalyzer* analyzer, AnalysisType t) = 0;
    
private:
    
    std::vector<std::vector<float>> _result;
    
};

#endif /* defined(__DFT__SpectralProcessor__) */
