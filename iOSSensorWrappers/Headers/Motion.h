//
//  Motion.h
//  APACoreMotion
//
//  Created by Danny van Swieten on 25-08-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APACoreMotion__Motion__
#define __APACoreMotion__Motion__

#import <CoreMotion/CoreMotion.h>

class APAMotion
{
public:
    //==============================================================================
    APAMotion();
    
    virtual ~APAMotion();
    
    virtual void accelerometerChanged (float x, float y, float z) = 0;
    virtual void gyrometerChanged (float x, float y, float z) = 0;
    
private:
    //==============================================================================
    CMMotionManager* motionManager;
    NSOperationQueue* queue;
};

#endif /* defined(__APACoreMotion__Motion__) */
