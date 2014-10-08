//
//  WaveFormComponent.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/30/14.
//
//

#include "WaveFormComponent.h"
#include "MainComponent.h"

WaveFormComponent::WaveFormComponent(APAudioFileManager* manager)
{
    _fileManager = manager;
}

WaveFormComponent::~WaveFormComponent()
{
    _fileManager = nullptr;
}

void WaveFormComponent::paint(Graphics& g)
{
    g.fillAll(Colour(Colours::white));
    
    Path drawPath;
    g.setOrigin(0, getHeight()/2);
    
    if(_fileManager->getNumberOfFiles())
    {
        APAudioFile audioFile = _fileManager->getFile(0);
        
        int step = audioFile.getNumSamples()/getWidth();
        int count = 0;
        
        for(auto i = 0; i < getWidth(); i++)
        {
            drawPath.lineTo(i, -audioFile.getAudioChannel(0)[count] * getHeight());
            count+= step;
        }
        g.strokePath(drawPath, PathStrokeType(1.0));
    }
}

void WaveFormComponent::resized()
{
    
}

void WaveFormComponent::mouseDown(const juce::MouseEvent &event)
{
    ModifierKeys modifiers = ModifierKeys::getCurrentModifiersRealtime();
    
    if(modifiers.isRightButtonDown())
    {
        PopupMenu menu;
        
        menu.addItem(1, "Load File");
        
        if (menu.show())
        {
            _fileManager->clearManager();
            FileChooser chooser("Please select the file you'd like to load",
                                File::getSpecialLocation(File::userHomeDirectory),
                                "*.wav; *.aiff",
                                true);
            
            if(chooser.browseForFileToOpen())
                _fileManager->loadFile(chooser.getResult());
        }
    }
    repaint();
}

void WaveFormComponent::mouseUp(const juce::MouseEvent &event)
{
    
}