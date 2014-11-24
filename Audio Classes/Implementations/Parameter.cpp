//
//  Parameter.
//  Engine
//
//  Created by Danny van Swieten on 07-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Parameter.h"

namespace APAudio
{
    namespace Audio
    {

        Parameter::Parameter(ControlValue min,
                             ControlValue max,
                             ControlValue start,
                             std::string identification)
        {
            minValue = min;
            maxValue = max;
            currentValue = start;
            
            ID = identification;
        }

        void Parameter::setMinValue(ControlValue value)
        {
            minValue = value;
        }

        void Parameter::setMaxValue(ControlValue value)
        {
            maxValue = value;
        }

        void Parameter::setValue(ControlValue value)
        {
            if (value <= maxValue)
                currentValue = value;
            else if (value > maxValue)
                currentValue = maxValue;
            else if (value < minValue)
                currentValue = minValue;
        }
    }
}