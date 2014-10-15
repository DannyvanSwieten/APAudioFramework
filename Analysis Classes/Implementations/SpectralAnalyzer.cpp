//
//  SpectralAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "SpectralAnalyzer.h"

SpectralAnalyzer::SpectralAnalyzer()
{

}

SpectralAnalyzer::~SpectralAnalyzer()
{

}

void SpectralAnalyzer::setN(int N)
{
    _N = N;
}

void SpectralAnalyzer::setOverlap(int overlap)
{
    _overlap = overlap;
}

void SpectralAnalyzer::setHopsize(int hopSize)
{
    _ra = hopSize;
    _ra = _N/_overlap;
}