//
//  APAudioAnalysisMenu.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/15/14.
//
//

#include "APAudioAnalysisMenu.h"

APAudioAnalysisMenu::APAudioAnalysisMenu(APAudioFileManager* fileManager,
                                         APAudioWindowManager* windowManager,
                                         WaveFormComponent* waveformComponent,
                                         Viewport* analysisViewport,
                                         FPTAnalyzerAudioProcessor* processor)
{
    _fileManager = fileManager;
    _windowManager = windowManager;
    _waveFormView = waveformComponent;
    _analysisViewport = analysisViewport;
    
    _loadFileButton = std::make_unique<TextButton>("Load Files");
    _loadFileButton->addListener(this);
    _loadFileButton->setBounds(0, 0, 100, 25);
    
    _analyzeButton = std::make_unique<TextButton>("Analyze and Draw");
    _analyzeButton->addListener(this);
    _analyzeButton->setBounds(2, 350, 100, 25);
    
    _playButton = std::make_unique<TextButton>("Play");
    _playButton->setBounds(0, 60, 100, 25);
    _playButton->addListener(this);
    
    _analysisMethod = std::make_unique<ComboBox>("Analysis Method");
    _analysisMethod->addItem("Fourier Transform", 1);
    _analysisMethod->addItem("Yin", 2);
    _analysisMethod->setBounds(2, 200, 200, 25);
    
    _analysisSize = std::make_unique<ComboBox>("Analysis Size");
    _analysisSize->addItem("512", 1);
    _analysisSize->addItem("1024", 2);
    _analysisSize->addItem("2048", 3);
    _analysisSize->addItem("4096", 4);
    _analysisSize->setBounds(2, 230, 200, 25);
    
    _windowSize = std::make_unique<ComboBox>("Window Size");
    _windowSize->addItem("512", 1);
    _windowSize->addItem("1024", 2);
    _windowSize->addItem("2048", 3);
    _windowSize->addItem("4096", 4);
    _windowSize->setBounds(2, 260, 200, 25);
    
    _windowType = std::make_unique<ComboBox>("Window Type");
    _windowType->addItem("Hanning", 1);
    _windowType->addItem("Blackman", 2);
    _windowType->setBounds(2, 290, 200, 25);
    
    _overlap = std::make_unique<ComboBox>("Overlap");
    _overlap->addListener(this);
    _overlap->addItem("1", 1);
    _overlap->addItem("2", 2);
    _overlap->addItem("4", 3);
    _overlap->addItem("8", 4);
    _overlap->setBounds(2, 320, 200, 25);
    
    _loadedFiles = std::make_unique<ComboBox>("Loaded Files");
    _loadedFiles->addListener(this);
    _loadedFiles->setBounds(2, 30, 200, 25);
    
    _process = std::make_unique<TextButton>("Process");
    _process->setBounds(2, 400, 200, 25);
    _process->addListener(this);
    
    addAndMakeVisible(_loadedFiles.get());
    addAndMakeVisible(_analysisMethod.get());
    addAndMakeVisible(_analysisSize.get());
    addAndMakeVisible(_windowSize.get());
    addAndMakeVisible(_windowType.get());
    addAndMakeVisible(_overlap.get());
    
    addAndMakeVisible(_loadFileButton.get());
    addAndMakeVisible(_analyzeButton.get());
    addAndMakeVisible(_playButton.get());
    addAndMakeVisible(_process.get());
    
    _processor = processor;
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
    
    if(buttonThatWasClicked == _playButton.get())
    {
        APAudioFile* file = _fileManager->getFile(_loadedFiles->getSelectedId()-1);
        
        _processor->_filePlayer->setFile(file);
        _processor->_filePlayer->setPlay();
    }
    
    if(buttonThatWasClicked == _analyzeButton.get())
    {
        int N = 0;
        int windowSize = 0;
        int overlap = 0;
        WindowType t;
        
        _analysisSize->getSelectedId();
        
        switch (_analysisSize->getSelectedId())
        {
            case 1:
                N = 512;
                break;
            case 2:
                N = 1024;
                break;
            case 3:
                N = 2048;
                break;
            case 4:
                N = 4096;
                break;
                
            default:
                break;
        }
        
        switch (_windowSize->getSelectedId())
        {
            case 1:
                windowSize = 512;
                break;
            case 2:
                windowSize = 1024;
                break;
            case 3:
                windowSize = 2048;
                break;
            case 4:
                windowSize = 4096;
                break;
                
            default:
                break;
        }
        
        switch (_overlap->getSelectedId())
        {
            case 1:
                overlap = 1;
                break;
            case 2:
                overlap = 2;
                break;
            case 3:
                overlap = 4;
                break;
            case 4:
                overlap = 8;
                break;
                
            default:
                break;
        }
        
        switch (_windowType->getSelectedId())
        {
            case 1:
                t = HANNING;
                break;
            case 2:
                t = BLACKMAN;
                break;
            case 3:
                overlap = 4;
                break;
            case 4:
                overlap = 8;
                break;
                
            default:
                break;
        }
        
        switch (_analysisMethod->getSelectedId())
        {
            case 1:
            {
                DFTSpectogram* spectogram = (DFTSpectogram*)_windowManager->getWindow(1);
                spectogram->getDrawData(_fileManager->getFile(_loadedFiles->getSelectedId()-1), N, windowSize, overlap, t);
                _analysisViewport->setViewedComponent(spectogram);
                break;
            }
                
            case 2:
            {
                PitchAnalysisWindow* pitchWindow = (PitchAnalysisWindow*)_windowManager->getWindow(2);
                pitchWindow->getDrawData(_fileManager->getFile(_loadedFiles->getSelectedId()-1), N, windowSize, overlap, t);
                _analysisViewport->setViewedComponent(pitchWindow);
            }
                
            default:
                break;
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