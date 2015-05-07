//
//  Motion.cpp
//  APACoreMotion
//
//  Created by Danny van Swieten on 25-08-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#include "Motion.h"

//==============================================================================
APAMotion::APAMotion()
{
    CMMotionManager* newManager = [[CMMotionManager alloc] init];
    motionManager = newManager;
    [motionManager startDeviceMotionUpdates];
    motionManager.deviceMotionUpdateInterval = 1.0/50.0;
    if (motionManager.accelerometerAvailable)
    {
        NSLog(@"Accelerometer avaliable");
        queue = [NSOperationQueue currentQueue];
    
        [motionManager startAccelerometerUpdatesToQueue:queue
                                            withHandler:^(CMAccelerometerData *accelerometerData,
                                                          NSError *error)
        {
            CMAcceleration acceleration = accelerometerData.acceleration;
            accelerometerChanged(acceleration.x, acceleration.y, acceleration.z);
        }];
     }
    else
        NSLog(@"No Accelerometer available in iOS Simulator");
    
    if (motionManager.gyroAvailable)
    {
        NSLog(@"Gyrometer avaliable");
        queue = [NSOperationQueue currentQueue];
        
        [motionManager startGyroUpdatesToQueue:queue
                                   withHandler:^(CMGyroData* gyrometerData,
                                                 NSError* error)
         {
             CMRotationRate gyrometer = gyrometerData.rotationRate;
             gyrometerChanged(gyrometer.x, gyrometer.y, gyrometer.z);
         }];
    }
    else
        NSLog(@"No Gyrometer available in iOS Simulator");
}

APAMotion::~APAMotion()
{
    
}