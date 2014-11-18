//
//  LowHighRatio.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/10/14.
//
//

#ifndef __FPTAnalyzer__LowHighRatio__
#define __FPTAnalyzer__LowHighRatio__

#include "../JuceLibraryCode/JuceHeader.h"
#include "APAudioFileManager2.h"
#include "DFTAnalyzer.h"

class LowHighRatio: public Component
{
public:
    LowHighRatio(APAudioFileManager* fileManager, DFTAnalyzer* analyzer);
    ~LowHighRatio();
    
    void resized()override;
    void paint(Graphics& g)override;
    void getDrawData(APAudioFile* audioFile, int N, int windowSize, int overlap, WindowType t);
    
private:
    
    Path _drawPath;
    APAudioFileManager* _fileManager;
    DFTAnalyzer* _analyzer;
};

#endif /* defined(__FPTAnalyzer__LowHighRatio__) */
