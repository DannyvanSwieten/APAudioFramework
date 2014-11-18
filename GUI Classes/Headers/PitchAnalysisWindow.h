//
//  PitchAnalysisWindow.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/4/14.
//
//

#ifndef __FPTAnalyzer__PitchAnalysisWindow__
#define __FPTAnalyzer__PitchAnalysisWindow__

#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent;

class PitchAnalysisWindow: public Component
{
public:

    PitchAnalysisWindow(MainContentComponent& mainComponent);
    ~PitchAnalysisWindow();
    
    void resized()override;
    void paint(Graphics& g)override;
    void getDrawData();
    void generateNamesAndFrequencies();
    int findNote(float frequency);
    std::string findNoteName(int bin);
private:
    
    MainContentComponent& _mainComponent;
    Path _drawPath;
    std::vector<std::vector<float>> _drawData;
    std::vector<float> _noteFrequencies;
    std::string _noteNames[12];
    bool _initialized = false;
};

#endif /* defined(__FPTAnalyzer__PitchAnalysisWindow__) */
