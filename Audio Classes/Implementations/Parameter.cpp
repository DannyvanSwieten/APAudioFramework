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
        Parameter::Parameter()
        {
            
        }

        void Parameter::setMinValue(ControlValue value)
        {
            _minValue = value;
        }

        void Parameter::setMaxValue(ControlValue value)
        {
            _maxValue = value;
        }

        void Parameter::setValue(ControlValue value)
        {
            if (value <= _maxValue)
                _currentValue = value;
            else if (value > _maxValue)
                _currentValue = _maxValue;
            else if (value < _minValue)
                _currentValue = _minValue;
        }
    }
}