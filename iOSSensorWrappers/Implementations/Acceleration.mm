//
//  Acceleration.cpp
//  APACoreMotion
//
//  Created by Danny van Swieten on 28-08-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Acceleration.h"

APAAcceleration::APAAcceleration(): APAMotion()
{
    
}

APAAcceleration::~APAAcceleration()
{
    
}

void APAAcceleration::accelerometerChanged(float x, float y, float z)
{
    _accelerometerData.x = x;
    _accelerometerData.y = y;
    _accelerometerData.z = z;
}

void APAAcceleration::gyrometerChanged(float x, float y, float z)
{
    _gyrometerData.x = x;
    _gyrometerData.y = y;
    _gyrometerData.z = z;
}