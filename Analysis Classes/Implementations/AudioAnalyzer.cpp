//
//  AudioAnalyzer.cpp
//  DFT
//
//  Created by Danny van Swieten on 9/18/14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer()
{

}

AudioAnalyzer::~AudioAnalyzer()
{

}

void AudioAnalyzer::setN(int N)
{
    _N = N;
}

void AudioAnalyzer::setOverlap(int overlap)
{
    _overlap = overlap;
}

void AudioAnalyzer::setHopsize(int hopSize)
{
    _ra = hopSize;
    _ra = _N/1;
}