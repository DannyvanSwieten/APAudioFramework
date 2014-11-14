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
#include "FrequencyAnalyzer.h"
#include "APAudioFileManager2.h"

class PitchAnalysisWindow: public Component
{
public:
    PitchAnalysisWindow(APAudioFileManager* fileManager, FrequencyAnalyzer* analyzer);
    ~PitchAnalysisWindow();
    
    void resized()override;
    void paint(Graphics& g)override;
    void getDrawData(APAudioFile* audioFile, int N, int windowSize, int overlap, WindowType t);
    void generateNamesAndFrequencies();
    int findNote(float frequency);
    std::string findNoteName(int bin);
private:
    
    Path _drawPath;
    APAudioFileManager* _fileManager;
    FrequencyAnalyzer* _analyzer;
    std::vector<float> _noteFrequencies;
    std::string _noteNames[12];
    bool _initialized = false;
};

#endif /* defined(__FPTAnalyzer__PitchAnalysisWindow__) */
