//
//  PitchAnalysisWindow.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 11/4/14.
//
//

#include "PitchAnalysisWindow.h"
#include "MainComponent.h"

PitchAnalysisWindow::PitchAnalysisWindow(MainContentComponent& mainComponent): _mainComponent(mainComponent)
{
    generateNamesAndFrequencies();
}

PitchAnalysisWindow::~PitchAnalysisWindow()
{
    
}

int PitchAnalysisWindow::findNote(float frequency)
{
    float low;
    float high;
    float overshoot;
    float halfPoint;
    
    if(frequency < _noteFrequencies[0] || frequency > _noteFrequencies[87])
        return -1;
    
    for(auto i = 0; i < 88-1; i++)
    {
        if(frequency < _noteFrequencies[i])
        {
            low = _noteFrequencies[i];
            high = _noteFrequencies[i+1];
            
            overshoot = frequency - low;
            halfPoint = (high - low) / 2;
            
            if(overshoot < halfPoint)
                return i;
            else
                return i+1;
        }
    }
    
    return -1;
}

std::string PitchAnalysisWindow::findNoteName(int bin)
{
    std::string note = _noteNames[bin %12] + std::to_string((bin/12) + 1);
    return note;
}

void PitchAnalysisWindow::generateNamesAndFrequencies()
{
    
    _noteNames[0] = "C";
    _noteNames[1] = "C#";
    _noteNames[2] = "D";
    _noteNames[3] = "D#";
    _noteNames[4] = "E";
    _noteNames[5] = "F";
    _noteNames[6] = "F#";
    _noteNames[7] = "G";
    _noteNames[8] = "G#";
    _noteNames[9] = "A";
    _noteNames[10] = "A#";
    _noteNames[11] = "B";
    
    float A4 = 440.0;
    float C5 = A4 * pow(2, 3.0/12.0);
    float C1 = C5 * pow(2, -4);
    
    _noteFrequencies.emplace_back(C1);
    for (auto i = 1; i < 88; i++)
    {
        _noteFrequencies.emplace_back(C1 * powf(2, i/12.0));
    }
}

void PitchAnalysisWindow::paint(Graphics& g)
{
    g.fillAll(Colours::whitesmoke);
    
    g.setOrigin(0, getHeight());
    int octave = 0;
    for (auto i = 0; i < 88; i++)
    {
        if(i % 12 == 0) octave++;
        
        g.drawRect(0, -20*i, getWidth(), 20);
        g.drawText(_noteNames[i % 12] + std::to_string(octave), 0, -20*(i+1), 30, 10, Justification::topLeft, false);
    }
    
    std::string file = _mainComponent.getMenu().getSelectedFile();
    
    if(_mainComponent.getAnalysisFactory().yinDataAvailable())
    {
        _drawPath.clear();
        g.setColour(juce::Colour(juce::Colours::black));
        
        auto drawScale = _mainComponent.getMenu().getDrawScale();
        
        int analysisSize = _mainComponent.getAnalysisFactory().getYinData(file).pitch.size();
        
        float rectSize = _mainComponent.getAnalysisFactory().getYinData(file).N/2;
        
        setSize((analysisSize * rectSize) / drawScale, getHeight());

        for(auto i = 0; i < analysisSize; i++)
        {
            float freq = _mainComponent.getAnalysisFactory().getYinData(file).pitch[i];
            float idealFreq = _noteFrequencies[findNote(freq)];
            float idealNextFreq = _noteFrequencies[findNote(freq) + 1];
            float idealPrevFreq = _noteFrequencies[findNote(freq) - 1];
            
            float maxDiv1 = (idealNextFreq - idealFreq) / 2.0;
            float maxDiv2 = (idealFreq - idealPrevFreq) / 2.0;
            
            int top = (findNote(freq) + 1) * 20;
            
            float freqDiv = freq - idealFreq;
            
            g.setColour(Colour(Colours::red));
            g.fillRect((i * (float)rectSize)/drawScale, (float)-top, rectSize/drawScale, 20.0);
            
            float scaledDiv;
            
            if(freqDiv != -1)
            {
                if (freqDiv > 0)
                    scaledDiv = scale(freqDiv, 0, maxDiv1, 0, 10);
                if(freqDiv < 0)
                    scaledDiv = scale(freqDiv, maxDiv2, 0, -10, 0);
                    
                _drawPath.lineTo((i * rectSize)/drawScale, (-top - 10) + scaledDiv);
            }
        }
        g.setColour(Colour(Colours::black));
        g.strokePath(_drawPath, PathStrokeType(1.0));
    }
}

void PitchAnalysisWindow::resized()
{
    
}

void PitchAnalysisWindow::getDrawData()
{
    _initialized = true;
}