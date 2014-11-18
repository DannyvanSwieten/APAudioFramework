//
//  AnalysisComponent.cpp
//  FPTAnalyzer 2
//
//  Created by Danny van Swieten on 11/14/14.
//
//

#include "AnalysisComponent.h"
#include "MainComponent.h"
#include "PitchAnalysisWindow.h"
#include "DFTSpectogram.h"

AnalysisComponent::AnalysisComponent(MainContentComponent& mainComponent): _mainComponent(mainComponent)
{
    _pitchWindow = std::make_unique<PitchAnalysisWindow>(_mainComponent);
    _pitchViewPort.setViewedComponent(_pitchWindow.get());
    
    _spectrogram = std::make_unique<DFTSpectogram>(_mainComponent);
    _spectrogramViewPort.setViewedComponent(_spectrogram.get());
    
    _tabbedComponent = std::make_unique<TabbedComponent>(TabbedButtonBar::Orientation::TabsAtTop);
    _tabbedComponent->addTab("Pitch", Colour(Colours::brown), &_pitchViewPort, false);
    _tabbedComponent->addTab("Spectrogram", Colour(Colours::brown), &_spectrogramViewPort, false);
    
    addAndMakeVisible(_tabbedComponent.get());
}

void AnalysisComponent::resized()
{
    _pitchWindow->setBounds(0, 0, (getWidth() / 6) *5, 88 * 20);
    _pitchViewPort.setBounds(0, 0, (getWidth() / 6) *5, getHeight());
    
    _spectrogramViewPort.setBounds(0, 0, (getWidth() / 6) *5, getHeight());
    _spectrogram->setBounds(0, 0, (getWidth() / 6) *5, getHeight());
    
    _tabbedComponent->setBounds(0, 0, (getWidth() / 6) *5, getHeight());
}

void AnalysisComponent::paint(Graphics& g)
{
    
}