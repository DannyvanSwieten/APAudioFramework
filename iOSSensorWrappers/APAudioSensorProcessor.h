//
//  APAudioSensorProcessor.h
//  FuChair
//
//  Created by Danny van Swieten on 10/9/14.
//
//

#ifndef __FuChair__APAudioSensorProcessor__
#define __FuChair__APAudioSensorProcessor__

#include "Acceleration.h"
#include <vector>
#include <complex>

class APAudioSensorProcessor
{
public:
    APAudioSensorProcessor();
    ~APAudioSensorProcessor();
    
    std::vector<float> getAngle();
    float getAcceleration();
    float rotationPerSecond();
    
private:
    
    
    APAAcceleration _sensor;
};

#endif /* defined(__FuChair__APAudioSensorProcessor__) */
