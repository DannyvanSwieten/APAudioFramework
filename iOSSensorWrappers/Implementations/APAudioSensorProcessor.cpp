//
//  APAudioSensorProcessor.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/9/14.
//
//

#include "APAudioSensorProcessor.h"

APAudioSensorProcessor::APAudioSensorProcessor()
{
    
}

APAudioSensorProcessor::~APAudioSensorProcessor()
{
    
}

float APAudioSensorProcessor::getAcceleration()
{
    _mutex.lock();
    return _sensor.getAccelerometerData()->z;
    _mutex.unlock();
}

float APAudioSensorProcessor::getAngle()
{
    _mutex.lock();
    float x = _sensor.getAccelerometerData()->x;
    float y = _sensor.getAccelerometerData()->y;
    float z = _sensor.getAccelerometerData()->z;
    
//    float x2 = x*x;
    float y2 = y*y;
    float z2 = z*z;
    
    float xResult = sqrt(y2 + z2);
    xResult = x/xResult;
    float angle = atan(xResult);
    
//    std::vector<float> angles;
//    
//    std::complex<float> angleZ(sqrt(x*x + y*y), z);
//    std::complex<float> angleY(sqrt(x*x + z*z), y);
//    std::complex<float> angleX(sqrt(y*y + z*z), x);
//    
//    angles.emplace_back(std::arg(angleX));
//    angles.emplace_back(std::arg(angleY));
//    angles.emplace_back(std::arg(angleZ));
    _mutex.unlock();
    return angle;
}