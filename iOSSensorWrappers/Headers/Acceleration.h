//
//  Acceleration.h
//  APACoreMotion
//
//  Created by Danny van Swieten on 28-08-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APACoreMotion__Acceleration__
#define __APACoreMotion__Acceleration__

struct GyrometerData
{
    float x;
    float y;
    float z;
};

struct AccelerometerData
{
    float x;
    float y;
    float z;
};

#include "Motion.h"

class APAAcceleration: public APAMotion
{
public:
    APAAcceleration();
    ~APAAcceleration();
    
    void accelerometerChanged (float x, float y, float z) override;
    void gyrometerChanged(float x, float y, float z) override;
    
    GyrometerData* getGyrometerData(){return &_gyrometerData;};
    AccelerometerData* getAccelerometerData(){return &_accelerometerData;};
    
private:
    
    GyrometerData _gyrometerData;
    AccelerometerData _accelerometerData;
};

#endif /* defined(__APACoreMotion__Acceleration__) */
