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
    _analyzer = std::make_unique<DFTAnalyzer>();
    _DFTSpectogramWindow = std::make_unique<DFTSpectogram>(manager, _analyzer.get());
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
            default:
            return nullptr;
    }
}