//
//  LowHighRatio.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/10/14.
//
//

#include "LowHighRatio.h"

LowHighRatio::LowHighRatio(APAudioFileManager* fileManager, DFTAnalyzer* analyzer)
{
    _fileManager = fileManager;
    _analyzer = analyzer;
}

LowHighRatio::~LowHighRatio()
{
    
}

void LowHighRatio::paint(Graphics& g)
{
    
}

void LowHighRatio::resized()
{
    
}

void LowHighRatio::getDrawData(APAudioFile *audioFile, int N, int windowSize, int overlap, WindowType t)
{
    _analyzer->init(N, overlap, t);
    _analyzer->readAndAnalyse(audioFile->getAudioChannel(0), audioFile->getNumSamples());
}