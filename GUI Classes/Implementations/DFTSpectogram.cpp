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
//    Result result = _shader->checkCompilation(g.getInternalContext());
//    if(result.wasOk())
//    {
//        _shader->fillRect(g.getInternalContext(), Rectangle<int>(0,0,getWidth(),getHeight()));
//    }
    
    if(_initalized)
    {

        g.setColour(juce::Colour(juce::Colours::black));

        int N = _analyzer->getWindowSize()/2.0;
        int analysisSize = _analyzer->getAmplitudes().size();
        float widthScale = (float)getWidth() / (analysisSize/2);
        float heightScale = (float)getHeight() / (N/10);

        auto rect = Rectangle<int>(widthScale , heightScale, widthScale, heightScale);
        
        for (auto i = 0; i < analysisSize; i++)
        {
            int counter = 0;
            for(auto j = N / 10; j > 0; j--)
            {
                float alpha = (float)_analyzer->getAmplitudes()[i][j];
                if(isnan(alpha)) alpha = 0;
                g.setColour(juce::Colour(255 - (alpha*255), 255 - (alpha*255*.5), 255 - (alpha*255 * .25)));

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
