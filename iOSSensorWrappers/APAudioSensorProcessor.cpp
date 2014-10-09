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
    return _sensor.getAccelerometerData()->x;
}

std::vector<float> APAudioSensorProcessor::getAngle()
{
    float x = _sensor.getAccelerometerData()->x;
    float y = _sensor.getAccelerometerData()->y;
    float z = _sensor.getAccelerometerData()->z;
    
    std::vector<float> angles;
    
    std::complex<float> angleZ(sqrt(x*x + y*y), z);
    std::complex<float> angleY(sqrt(x*x + z*z), y);
    std::complex<float> angleX(sqrt(y*y + z*z), x);
    
//    std::cout<<std::arg(angleX)<<" "<<arg(angleY)<<" "<<arg(angleZ)<<std::endl;
    
    angles.emplace_back(std::arg(angleX));
    angles.emplace_back(std::arg(angleY));
    angles.emplace_back(std::arg(angleZ));
    
    return angles;
}