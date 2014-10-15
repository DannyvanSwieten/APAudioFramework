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
    _DFTSpectogramWindow = std::make_unique<DFTSpectogram>(manager);
}

APAudioWindowManager::~APAudioWindowManager()
{
    
}

Component* APAudioWindowManager::showWindow(int index)
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