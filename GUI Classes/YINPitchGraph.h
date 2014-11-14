//
//  YINPitchGraph.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/16/14.
//
//

#ifndef __FPTAnalyzer__YINPitchGraph__
#define __FPTAnalyzer__YINPitchGraph__

#include "../JuceLibraryCode/JuceHeader.h"
#include "YINAnalyzer.h"
#include "APAudioFileManager2.h"

class YINPitchGraph: public Component
{
public:
    YINPitchGraph(APAudioFileManager* fileManager, YINAnalyzer* analyzer);
    YINPitchGraph();
    
    void resized() override final;
    void paint(Graphics& g) override final;
    
private:
    
    
    
};

#endif /* defined(__FPTAnalyzer__YINPitchGraph__) */
