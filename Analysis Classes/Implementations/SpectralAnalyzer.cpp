//
//  SpectralAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "SpectralAnalyzer.h"

SpectralAnalyzer::SpectralAnalyzer(unsigned int N, unsigned int overlap)
{
    _N = N;
    _overlap = overlap;
    _ra = _N/_overlap;
}

SpectralAnalyzer::~SpectralAnalyzer()
{

}