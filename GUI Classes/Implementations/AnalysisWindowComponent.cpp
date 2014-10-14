//
//  FFTDrawWindow.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/25/14.
//
//

#include "MainComponent.h"

AnalysisWindowComponent::AnalysisWindowComponent(APAudioFileManager* fileManager) :
    _fileManager(fileManager)
{

}

AnalysisWindowComponent::~AnalysisWindowComponent()
{
    _fileManager = nullptr;
}

void AnalysisWindowComponent::resized()
{
    
}

void AnalysisWindowComponent::mouseDown(const juce::MouseEvent &event)
{
    ModifierKeys modifiers = ModifierKeys::getCurrentModifiersRealtime();
    
    if(modifiers.isPopupMenu())
    {
        PopupMenu menu;
        PopupMenu DFT;
        PopupMenu wavelet;
        PopupMenu fastWavelet;
        
        DFT.addItem(1, "Spectogram");
        DFT.addItem(2, "Spectral Flux");
        DFT.addItem(3, "Phase Difference");
        
        wavelet.addItem(4, "Spectogram");
        wavelet.addItem(5, "Spectral Flux");
        wavelet.addItem(6, "Phase Difference");
        
        fastWavelet.addItem(7, "Spectogram");
        fastWavelet.addItem(8, "Spectral Flux");
        fastWavelet.addItem(9, "Phase Difference");
        
        
        menu.addSubMenu("DFT", DFT);
        menu.addSubMenu("Wavelet", wavelet);
        menu.addSubMenu("Fast Lifting Wavelet", fastWavelet);
        
        menu.addItem(10, "Frequency");
        
        switch (menu.show())
        {
            case 0:
                return;
            case 5:
//                computeDFTSpectralFlux();
                // Dodfgdfg f in path
                break;
        }
    }
    
    repaint();
}

void AnalysisWindowComponent::mouseUp(const juce::MouseEvent &event)
{
    
}

void AnalysisWindowComponent::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    
    g.setColour(Colours::black);
    g.strokePath(_drawPath, PathStrokeType(1.0));
}

void AnalysisWindowComponent::getDrawData()
{
    
}

void AnalysisWindowComponent::drawScale(Graphics& g)
{

}

void AnalysisWindowComponent::drawFrequency(juce::Graphics &g)
{
    _drawPath.clear();
    g.setColour(Colour(Colours::black));
    FrequencyAnalyzer analyzer(1024);
    if(!_drawPathWasSet)
    {
        analyzer.readAndAnalyse(_fileManager->getFile(0)->getAudioChannel(0), _fileManager->getFile(0)->getNumSamples());

        int analysisSize = _fileManager->getFile(0)->getNumSamples() / 10;
        int step = analysisSize / getWidth();
        float heightScale = (float)getHeight() / 800.0;
        int count = 0;
        
        g.setOrigin(0, getHeight());
        
        for(auto j = 0; j < getWidth(); j++)
        {
            float frequency = analyzer.getResult()[count];
            if (isnan(frequency) ||  frequency == -1 || frequency > 800) frequency = 0;
            _drawPath.lineTo(j, frequency * -heightScale);
            count+=step;
        }
    }
    
    g.strokePath(_drawPath, PathStrokeType(1.0));
}

void AnalysisWindowComponent::drawTransientData(juce::Graphics& g)
{

}

void AnalysisWindowComponent::drawDFTSpectogram(juce::Graphics& g)
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

void AnalysisWindowComponent::drawWaveletSpectogram(juce::Graphics &g)
{

}

void AnalysisWindowComponent::drawSpectralFlux(juce::Graphics &g)
{
//    _drawPath.clear();
//    
//    DFTAnalyzer analyzer(1024, 1, HANNING);
//
//    analyzer.readAndAnalyse(_fileManager->getFile(0)->getAudioChannel(0), _fileManager->getFile(0)->getNumSamples());
//    analyzer.calculateAmplitudes();
//    analyzer.calculateSpectralFlux();
//
////    g.setColour(juce::Colour(juce::Colours::black));
////    g.setOrigin(0, getHeight());
////    
////    int analysisSize = _fileManager->getFile(0)->getNumSamples() / 1024;
////    
////    float step = (getWidth() / analysisSize);
////    float count = 0;
//
//    for(auto i = 0; i < 100; i++)
//    {
////        float y = -analyzer.getSpectralFlux()[i];
////        if(isnan(y)) y = 0;
////        _drawPath.lineTo(count, y * getHeight());
////        count += step;
//        
//        _drawPath.lineTo(i, i);
//    }
    
    g.fillAll(Colours::red);
    g.setColour(Colours::white);
    g.strokePath(_drawPath, PathStrokeType(1.0));
}
