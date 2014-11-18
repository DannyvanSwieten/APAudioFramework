//
//  AnalysisWindowComponent.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/30/14.
//
//

#ifndef FPTAnalyzer_AnalysisWindowComponent_h
#define FPTAnalyzer_AnalysisWindowComponent_h

#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"
class MainContentComponent;

class DFTSpectogram: public Component
{
public:
    
    DFTSpectogram(MainContentComponent& mainComponent);
    ~DFTSpectogram();
    
    void resized() override final;
    void paint(Graphics& g) override final;
    void getDrawData();
    void mouseUp (const MouseEvent& event) override final;
    void mouseDown(const MouseEvent& event) override final;
    
private:
    
    MainContentComponent& _mainComponent;
    bool _initalized = false;
    
    void drawScale(Graphics& g);

    bool _dataWasRead = 0;
    bool _drawPathWasSet = 0;
    Path _drawPath;
};

#endif
