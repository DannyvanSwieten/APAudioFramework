//
//  AnalysisComponent.h
//  FPTAnalyzer 2
//
//  Created by Danny van Swieten on 11/14/14.
//
//

#ifndef __FPTAnalyzer_2__AnalysisComponent__
#define __FPTAnalyzer_2__AnalysisComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "DFTSpectogram.h"
#include "PitchAnalysisWindow.h"

class MainContentComponent;

class AnalysisComponent: public Component
{
public:
    
    AnalysisComponent(MainContentComponent& mainComponent);
    void paint (Graphics&);
    void resized();
    
private:
    
    MainContentComponent& _mainComponent;
    std::unique_ptr<TabbedComponent> _tabbedComponent;
    
    Viewport _pitchViewPort;
    std::unique_ptr<PitchAnalysisWindow> _pitchWindow;
    
    Viewport _spectrogramViewPort;
    std::unique_ptr<DFTSpectogram> _spectrogram;
};

#endif /* defined(__FPTAnalyzer_2__AnalysisComponent__) */
