//
//  FFTDrawWindow.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/25/14.
//
//

#include "DFTSpectogram.h"
#include "MainComponent.h"

DFTSpectogram::DFTSpectogram(MainContentComponent& mainComponent): _mainComponent(mainComponent)
{

}

DFTSpectogram::~DFTSpectogram()
{
    
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
    
    if(_mainComponent.getAnalysisFactory().fourierDataAvailable())
    {
        g.setColour(juce::Colour(juce::Colours::black));
        std::string file = _mainComponent.getMenu().getSelectedFile();
        
        auto drawScale = _mainComponent.getMenu().getDrawScale();
        
        int N = _mainComponent.getAnalysisFactory().getFourierData(file).N;
        
        int analysisSize = _mainComponent.getAnalysisFactory().getFourierData(file).amplitudes.size();
        float heightScale = (float)getHeight() / (N/10);
        
        setSize((analysisSize * N) / drawScale , getHeight());

        for (auto i = 0; i < analysisSize; i++)
        {
            int counter2 = 0;
            for(auto j = N / 10; j > 1; j--)
            {
                float alpha = _mainComponent.getAnalysisFactory().getFourierData(file).amplitudes[i][j]; //* (float)_analyzer->_getPeaks()[(int)counter][j];
                if(isnan(alpha)) alpha = 0;
                g.setColour(juce::Colour(255 - (alpha*255), 255 - (alpha*255*.7), 255 - (alpha*255 * .3)));

                g.fillRect((float)i * N / drawScale ,
                           heightScale * counter2++,
                           (float)N / drawScale,
                           heightScale);
                
            }
        }
    }
}

void DFTSpectogram::getDrawData()
{
    _initalized = true;
}

void DFTSpectogram::drawScale(Graphics& g)
{

}
