//
//  TransientProcessor.h
//  DFT
//
//  Created by Danny van Swieten on 9/20/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __DFT__TransientProcessor__
#define __DFT__TransientProcessor__

#include "SpectralProcessor.h"
#include "DFTAnalyzer.h"
#include <iostream>

class TransientProcessor: public SpectralProcessor
{
public:
    void processTransients(SpectralAnalyzer* analyser, AnalysisType t) override;
    std::vector<float> getResult(){return _result;};
private:
    
    void processDFT(DFTAnalyzer* dftAnalyser);
    std::vector<float> _result;
};

#endif /* defined(__DFT__TransientProcessor__) */
