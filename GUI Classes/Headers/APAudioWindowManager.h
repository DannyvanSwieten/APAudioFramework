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
#include "YINAnalyzer.h"

class APAudioWindowManager
{
public:
    APAudioWindowManager(APAudioFileManager* manager);
    ~APAudioWindowManager();
    
    Component* getWindow(int index);
    
private:
    
    std::unique_ptr<DFTAnalyzer> _dftAnalyzer;
    std::unique_ptr<YINAnalyzer> _yinAnalyzer;
    
    std::unique_ptr<DFTSpectogram> _DFTSpectogramWindow;
};

#endif /* defined(__FPTAnalyzer__APAudioWindowManager__) */
