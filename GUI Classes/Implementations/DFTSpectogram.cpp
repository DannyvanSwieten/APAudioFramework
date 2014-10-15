//
//  FFTDrawWindow.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/25/14.
//
//

#include "DFTSpectogram.h"

DFTSpectogram::DFTSpectogram(APAudioFileManager* fileManager) :
    _fileManager(fileManager)
{

}

DFTSpectogram::DFTSpectogram()
{
    _fileManager = nullptr;
}

void DFTSpectogram::resized()
{
    
}

void DFTSpectogram::mouseDown(const juce::MouseEvent &event)
{

}

void DFTSpectogram::mouseUp(const juce::MouseEvent &event)
{
    
}

void DFTSpectogram::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    
    g.setColour(Colours::black);
    g.strokePath(_drawPath, PathStrokeType(1.0));
}

void DFTSpectogram::getDrawData()
{
    
}

void DFTSpectogram::drawScale(Graphics& g)
{

}

void DFTSpectogram::drawDFTSpectogram(juce::Graphics& g)
{
    DFTAnalyzer analyzer(1024, 1, HANNING);
    
    analyzer.readAndAnalyse(_fileManager->getFile(0)->getAudioChannel(0), _fileManager->getFile(0)->getNumSamples());
    analyzer.calculateAmplitudes();
    analyzer.calculateSpectralFlux();
    
    g.setColour(juce::Colour(juce::Colours::black));
    
    int N = analyzer.getWindowSize()/2.0;
    int analysisSize = analyzer.getAmplitudes().size();
    float widthScale = (float)getWidth() / (analysisSize/2);
    float heightScale = (float)getHeight() / (N/2);
    
    for (auto i = 0; i < analysisSize; i++)
    {
        int counter = 0;
        for(auto j = N / 2; j > 0; j--)
        {
            float alpha = (float)analyzer.getAmplitudes()[i][j];
            if(isnan(alpha)) alpha = 0;
            g.setColour(juce::Colour(juce::Colours::black.withAlpha(alpha)));
            
            g.fillRect(widthScale * i ,
                       heightScale * counter++,
                       widthScale,
                       heightScale);
        }
    }
}
