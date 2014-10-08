//
//  APAudioParameter.
//  APAudioEngine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "APAudioParameter.h"

APAudioParameter::APAudioParameter(ControlValue min,
                                         ControlValue max,
                                         ControlValue start,
                                         juce::String identification)
{
    minValue = min;
    maxValue = max;
    currentValue = start;
    
    ID = identification;
}

void APAudioParameter::setMinValue(ControlValue value)
{
    minValue = value;
}

void APAudioParameter::setMaxValue(ControlValue value)
{
    maxValue = value;
}

void APAudioParameter::setValue(ControlValue value)
{
    if (value <= maxValue)
        currentValue = value;
    else if (value > maxValue)
        currentValue = maxValue;
    else if (value < minValue)
        currentValue = minValue;
}