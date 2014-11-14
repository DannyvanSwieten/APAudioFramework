//
//  FFTDrawWindow.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 9/25/14.
//
//

#include "DFTSpectogram.h"

DFTSpectogram::DFTSpectogram(APAudioFileManager* fileManager, DFTAnalyzer* analyzer)
{
    _analyzer = analyzer;
    _fileManager = fileManager;
    setBufferedToImage(true);
    
    _glContext.attachTo(*this);
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
    
    if(_initalized)
    {

        g.setColour(juce::Colour(juce::Colours::black));

        int N = _analyzer->getWindowSize()/2.0;
        int analysisSize = _analyzer->getAmplitudes().size();
        float heightScale = (float)getHeight() / (N/10);
        
        float step = (float)analysisSize/(float)getWidth();

        float counter = 0;
        for (auto i = 0; i < getWidth(); i++)
        {
            int counter2 = 0;
            for(auto j = N / 10; j > 1; j--)
            {
                float alpha = _analyzer->getAmplitudes()[(int)counter][j] * (float)_analyzer->_getPeaks()[(int)counter][j];
                if(isnan(alpha)) alpha = 0;
                g.setColour(juce::Colour(255 - (alpha*255), 255 - (alpha*255*.7), 255 - (alpha*255 * .3)));

                g.fillRect((float)i * 2 ,
                           heightScale * counter2++,
                           2.0,
                           heightScale);
                
            }
            counter+=step;
        }
    }
}

void DFTSpectogram::getDrawData(APAudioFile* audioFile, int N, int windowSize, int overlap, WindowType t)
{
    _analyzer->init(N, overlap, t);
    _analyzer->readAndAnalyse(audioFile->getAudioChannel(0), audioFile->getNumSamples());
    _analyzer->calculateAmplitudes();
    _analyzer->generatePeakMap();
    _analyzer->searchStableSinusoids();
    _analyzer->calculatePhases();
    _initalized = true;
}

void DFTSpectogram::drawScale(Graphics& g)
{

}
