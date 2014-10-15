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

void WaveFormComponent::loadData(APAudioFile *file)
{
    _drawPath.clear();
    int step = file->getNumSamples()/getWidth();
    int count = 0;
    
    for(auto i = 0; i < getWidth(); i++)
    {
        _drawPath.lineTo(i, -file->getAudioChannel(0)[count] * getHeight());
        count+= step;
    }
}

void WaveFormComponent::paint(Graphics& g)
{
    g.fillAll(Colour(Colours::white));
    g.setOrigin(0, getHeight()/2);
    
    g.strokePath(_drawPath, PathStrokeType(1.0));
}

void WaveFormComponent::resized()
{
    
}

void WaveFormComponent::mouseDown(const juce::MouseEvent &event)
{

}

void WaveFormComponent::mouseUp(const juce::MouseEvent &event)
{
    
}