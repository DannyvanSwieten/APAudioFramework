//
//  APAudioWindowManager.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/14/14.
//
//

#include "APAudioWindowManager.h"

APAudioWindowManager::APAudioWindowManager(APAudioFileManager* manager)
{
    _dftAnalyzer = std::make_unique<DFTAnalyzer>(0, 0, HAMMING);
    _yinAnalyzer = std::make_unique<FrequencyAnalyzer>();
    
    _DFTSpectogramWindow = std::make_unique<DFTSpectogram>(manager, _dftAnalyzer.get());
    _pitchAnalysisWindow = std::make_unique<PitchAnalysisWindow>(manager, _yinAnalyzer.get());
    _ratioWindow= std::make_unique<LowHighRatio>(manager, _dftAnalyzer.get());
}

APAudioWindowManager::~APAudioWindowManager()
{
    
}

Component* APAudioWindowManager::getWindow(int index)
{
    switch (index)
    {
        case 1:
        {
            return _DFTSpectogramWindow.get();
            break;
        }
            
        case 2:
        {
            return _pitchAnalysisWindow.get();
            break;
        }
            
        case 3:
        {
            return _ratioWindow.get();
            break;
        }
            default:
            return nullptr;
    }
}