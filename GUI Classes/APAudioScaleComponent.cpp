//
//  APAudioScaleComponent.cpp
//  FPTAnalyzer
//
//  Created by Danny van Swieten on 10/16/14.
//
//

#include "APAudioScaleComponent.h"

APAudioScaleComponent::APAudioScaleComponent()
{

}

APAudioScaleComponent::~APAudioScaleComponent()
{
    
}

void APAudioScaleComponent::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    
    if(_hasAudio)
    {
        g.setColour(Colour(Colours::black));
        int count = 0;
        
        if(_maxValue < 10)
        {
            for(auto i = 0; i < getWidth(); i+=_stepSize)
            {
                g.drawText(std::to_string(count++), (float)i * _stepSize, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine((float)i * _stepSize, 0, getHeight());
            }
        }
        count = 0;
        if(_maxValue < 100 && _maxValue > 10)
        {
            for(auto i = 0; i < getWidth(); i+=_stepSize)
            {
                g.drawText(std::to_string((count++ * 10/ _zoom)), (float)i, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine(i, 0, getHeight());
            }
        }
        count = 0;
        if(_maxValue < 1000 && _maxValue > 100)
        {
            for(auto i = 0; i < getWidth(); i+=_stepSize)
            {
                g.drawText(std::to_string((count++ * 100/ _zoom)), (float)i, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine((float)i, 0, getHeight());
            }
        }
        count = 0;
        if(_maxValue < 10000 && _maxValue > 1000)
        {
            for(auto i = 0; i < getWidth(); i+= _stepSize)
            {
                g.drawText(std::to_string((count++ * 1000/ _zoom)), (float)i, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine((float)i, 0, getHeight());
            }
        }
        count = 0;
        if(_maxValue < 100000 && _maxValue > 10000)
        {
            for(auto i = 0; i < getWidth(); i+= _stepSize)
            {
                g.drawText(std::to_string((count++ * 10000/ _zoom)), (float)i, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine((float)i, 0, getHeight());
            }
        }
        count = 0;
        if(_maxValue < 1000000 && _maxValue > 100000)
        {
            for(auto i = 0; i < getWidth(); i+= _stepSize)
            {
                g.drawText(std::to_string(count++ * (100000 / _zoom)), (float)i, getHeight()/2, 75, 10, Justification::left, 0);
                g.drawVerticalLine((float)i, 0, getHeight());
            }
        }
    }
}

void APAudioScaleComponent::resized()
{
    
}

void APAudioScaleComponent::setZoom(int zoom)
{
    _zoom = zoom;
}

void APAudioScaleComponent::setValues(int max, int sampleRate)
{
    _maxValue = max;
    _stepSize = (getWidth() / 10) / _zoom;
    
    _hasAudio = true;
}