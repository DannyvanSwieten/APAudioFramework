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
        float widthScale = (float)getWidth() / (analysisSize/2);
        float heightScale = (float)getHeight() / (N/2);

        for (auto i = 0; i < analysisSize; i++)
        {
            int counter = 0;
            for(auto j = N / 2; j > 0; j--)
            {
                float alpha = (float)_analyzer->getAmplitudes()[i][j];
                if(isnan(alpha)) alpha = 0;
                g.setColour(juce::Colour(juce::Colours::black.withAlpha(alpha)));

                g.fillRect(widthScale * i ,
                           heightScale * counter++,
                           widthScale,
                           heightScale);
            }
        }
    }
}

void DFTSpectogram::getDrawData(APAudioFile* audioFile, int N, int windowSize, int overlap)
{
    _analyzer->init(N, overlap, HANNING);
    _analyzer->readAndAnalyse(audioFile->getAudioChannel(0), audioFile->getNumSamples());
    _analyzer->calculateAmplitudes();
    _initalized = true;
}

void DFTSpectogram::drawScale(Graphics& g)
{

}
