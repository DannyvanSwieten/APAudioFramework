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
    _timeScale = std::make_unique<APAudioScaleComponent>();
    addAndMakeVisible(_timeScale.get());
}

WaveFormComponent::~WaveFormComponent()
{

}

void WaveFormComponent::fillPath()
{
    int step = _file->getNumSamples()/getWidth();
    if(step < 1) step = 1;
    int count = 0;
    _drawPath.clear();
    
    for(auto i = 0; i < getWidth(); i++)
    {
        _drawPath.lineTo(i, -_file->getAudioChannel(0)[count] * (getHeight()-20));
        count += step;
    }
}

void WaveFormComponent::loadData(APAudioFile *file)
{
    _file = file;
    _timeScale->setValues(file->getNumSamples(), file->getSampleRate());
    fillPath();
}

void WaveFormComponent::paint(Graphics& g)
{
    g.fillAll(Colour(Colours::white));
    g.setOrigin(0, getHeight()/2);
    
    g.strokePath(_drawPath, PathStrokeType(1.0));
}

void WaveFormComponent::resized()
{
    _timeScale->setBounds(0, getHeight()-20, getWidth(), 20);
}

void WaveFormComponent::mouseDown(const juce::MouseEvent &event)
{

}

void WaveFormComponent::mouseUp(const juce::MouseEvent &event)
{
    if(getWidth()*2 >! _file->getNumSamples())
    {
        _zoom *= 2;
        _timeScale->setZoom(_zoom);
        _timeScale->setValues(_file->getNumSamples()/_zoom, 44100);
        setBounds(0, 0, getWidth()*2, getHeight());
        fillPath();
    }
}