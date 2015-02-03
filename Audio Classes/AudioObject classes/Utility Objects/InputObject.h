//
//  InputObject.h
//  VSTHost
//
//  Created by Danny van Swieten on 2/1/15.
//  Copyright (c) 2015 Danny van Swieten. All rights reserved.
//

#ifndef __VSTHost__InputObject__
#define __VSTHost__InputObject__

#include "AudioObject.h"

class InputObject: public APAudio::AudioObject
{
public:
    InputObject(APAudio::Mainframe& mf_);
    void calculateBuffer()override;
    void feed(float* input);
    void enableInput();
    void disableInput();
private:
    
    float* input;
    bool inputEnabled = false;
};

#endif /* defined(__VSTHost__InputObject__) */
