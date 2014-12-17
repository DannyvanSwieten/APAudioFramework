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

#include "AudioFileManager.h"
#include "AnalysisFactory.h"

class MainContentComponent;

class APAudioAnalysisMenu: public Component, public Button::Listener, public ComboBox::Listener, public Slider::Listener
{
public:
    
    class AnalysisDescription
    {
    public:
        
        int N;
        int windowSize;
        int overlop;
        WindowType t;
        APAudio::Analysis::AnalysisFactory::ANALYSISMETHOD method;
        APAudio::Analysis::AnalysisFactory::ANALYSISRESULT result;
    };
    
    APAudioAnalysisMenu(MainContentComponent& mainComponent);
    
    ~APAudioAnalysisMenu();
    
    void resized() override final;
    void paint(Graphics& g) override final;
    void buttonClicked(Button* buttonThatWhasClicked)override final;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged)override final;
    void sliderValueChanged (Slider* slider) override final;
    std::string getSelectedFile() const {return _loadedFiles.getText().toStdString();};
    float getDrawScale(){return _drawScale;};
private:
    
    MainContentComponent& _mainComponent;
    
    ComboBox _analysisMethod;
    ComboBox _analysisSize;
    ComboBox _windowSize;
    ComboBox _windowType;
    ComboBox _overlap;
    ComboBox _loadedFiles;
    
    TextButton _loadFileButton;
    TextButton _analyzeButton;
    TextButton _playButton;
    TextButton _process;
    
    Slider _scale;
    
    AnalysisDescription _description;
    
    float _drawScale = 1;
    bool _initialized;

};

#endif /* defined(__FPTAnalyzer__APAudioAnalysisMenu__) */
