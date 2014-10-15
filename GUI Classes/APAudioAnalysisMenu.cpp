//
//  APAudioAnalysisMenu.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/15/14.
//
//

#include "APAudioAnalysisMenu.h"

APAudioAnalysisMenu::APAudioAnalysisMenu(APAudioFileManager* fileManager, APAudioWindowManager* windowManager, WaveFormComponent* waveformComponent)
{
    _fileManager = fileManager;
    _windowManager = windowManager;
    _waveFormView = waveformComponent;
    
    _loadFileButton = std::make_unique<TextButton>("Load Files");
    _loadFileButton->setBounds(0, 0, 100, 25);
    _loadFileButton->addListener(this);
    
    addAndMakeVisible(_loadFileButton.get());
    
    _analysisMethod = std::make_unique<ComboBox>("Analysis Method");
    _analysisSize = std::make_unique<ComboBox>("Analysis Method");
    _windowSize = std::make_unique<ComboBox>("Window Size");
    _windowType = std::make_unique<ComboBox>("Window Type");
    _overlap = std::make_unique<ComboBox>("Overlap");
    _loadedFiles = std::make_unique<ComboBox>("Loaded Files");
    _loadedFiles->addListener(this);
    
    _loadedFiles->setBounds(110, 0, 100, 25);
    _analysisMethod->setBounds(0, 300, 100, 25);
    
    addAndMakeVisible(_loadedFiles.get());
    addAndMakeVisible(_analysisMethod.get());
    addAndMakeVisible(_analysisSize.get());
    addAndMakeVisible(_windowSize.get());
    addAndMakeVisible(_windowType.get());
    addAndMakeVisible(_overlap.get());
}

APAudioAnalysisMenu::~APAudioAnalysisMenu()
{
    
}

void APAudioAnalysisMenu::buttonClicked(Button* buttonThatWasClicked)
{
    if(buttonThatWasClicked == _loadFileButton.get())
    {
        Array<File> files;
        FileChooser chooser("Please select the file you'd like to load",
                            File::getSpecialLocation(File::userHomeDirectory),
                            "*.wav; *.aiff",
                            true);
        
        if(chooser.browseForMultipleFilesToOpen())
        {
            _fileManager->clearManager();
            _loadedFiles->clear();
            files = chooser.getResults();
        
            for(auto i = 0; i < files.size(); i++)
            {
                _fileManager->loadFile(files[i]);
                _loadedFiles->addItem(files[i].getFileName(), i+1);
            }
        }
    }
}

void APAudioAnalysisMenu::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == _loadedFiles.get())
    {
        if(comboBoxThatHasChanged->getSelectedId() != 0)
        {
            _waveFormView->loadData(_fileManager->getFile(comboBoxThatHasChanged->getSelectedId()-1));
            _waveFormView->repaint();
        }
    }
}

void APAudioAnalysisMenu::paint(Graphics& g)
{
    g.fillAll(Colour(Colours::white));
}

void APAudioAnalysisMenu::resized()
{
    
}