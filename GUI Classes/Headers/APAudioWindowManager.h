//
//  APAudioWindowManager.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/14/14.
//
//

#ifndef __FPTAnalyzer__APAudioWindowManager__
#define __FPTAnalyzer__APAudioWindowManager__

#include "DFTSpectogram.h"

class APAudioWindowManager
{
public:
    APAudioWindowManager(APAudioFileManager* manager);
    ~APAudioWindowManager();
    
    Component* getWindow(int index);
    
private:
    
    std::unique_ptr<DFTAnalyzer> _analyzer;
    std::unique_ptr<DFTSpectogram> _DFTSpectogramWindow;
};

#endif /* defined(__FPTAnalyzer__APAudioWindowManager__) */
