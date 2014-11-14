//
//  APAudioAnalysisMenu.h
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/15/14.
//
//

#ifndef __FPTAnalyzer__APAudioAnalysisMenu__
#define __FPTAnalyzer__APAudioAnalysisMenu__

#include "../JuceLibraryCode/JuceHeader.h"

#include "APAudioFileManager2.h"
#include "APAudioWindowManager.h"
#include "WaveFormComponent.h"
#include "FPTAnalyzerAudioProcessor.h"
#include "PitchAnalysisWindow.h"

class APAudioAnalysisMenu: public Component, public Button::Listener, public ComboBox::Listener
{
public:
    
    APAudioAnalysisMenu(APAudioFileManager* fileManager,
                        APAudioWindowManager* windowManager,
                        WaveFormComponent* waveformComponent,
                        Viewport* viewport,
                        FPTAnalyzerAudioProcessor* processor);
    
    ~APAudioAnalysisMenu();
    
    void resized() override final;
    void paint(Graphics& g) override final;
    void buttonClicked(Button* buttonThatWhasClicked)override final;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged)override final;
    
private:
    
    std::unique_ptr<ComboBox> _analysisMethod;
    std::unique_ptr<ComboBox> _analysisSize;
    std::unique_ptr<ComboBox> _windowSize;
    std::unique_ptr<ComboBox> _windowType;
    std::unique_ptr<ComboBox> _overlap;
    std::unique_ptr<ComboBox> _loadedFiles;
    
    std::unique_ptr<TextButton> _loadFileButton;
    std::unique_ptr<TextButton> _analyzeButton;
    std::unique_ptr<TextButton> _playButton;
    std::unique_ptr<TextButton> _process;
    
    WaveFormComponent* _waveFormView;
    APAudioFileManager* _fileManager;
    APAudioWindowManager* _windowManager;
    FPTAnalyzerAudioProcessor* _processor;
    Viewport* _analysisViewport;
    
    bool _initialized;

};

#endif /* defined(__FPTAnalyzer__APAudioAnalysisMenu__) */
