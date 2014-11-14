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
#include "PitchAnalysisWindow.h"
#include "FrequencyAnalyzer.h"
#include "LowHighRatio.h"

class APAudioWindowManager
{
public:
    APAudioWindowManager(APAudioFileManager* manager);
    ~APAudioWindowManager();
    
    Component* getWindow(int index);
    std::unique_ptr<DFTAnalyzer> _dftAnalyzer;
    
private:
    
    std::unique_ptr<FrequencyAnalyzer> _yinAnalyzer;
    
    std::unique_ptr<LowHighRatio> _ratioWindow;
    std::unique_ptr<DFTSpectogram> _DFTSpectogramWindow;
    std::unique_ptr<PitchAnalysisWindow> _pitchAnalysisWindow;
};

#endif /* defined(__FPTAnalyzer__APAudioWindowManager__) */
