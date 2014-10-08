//
//  APAudioDecimatorModule.h
//  APAudioEngine
//
//  Created by Danny van Swieten on 10-05-14.
//  Copyright (c) 2014 Danny van Swieten. All rights reserved.
//

#ifndef __APAudioEngine__APAudioDecimatorModule__
#define __APAudioEngine__APAudioDecimatorModule__

#include "APAudioModule.h"

class APAudioDecimatorModule: public APAudioModule
{
public:
    
    APAudioDecimatorModule(APAudioMainFrame* mf);
    
    void calculateBuffer() override final;
    void setBitRate(UInt rate);
    
    inline UInt getBitRate(){return bitRate;};
    
private:
    
    UInt bitRate;
    UInt step;
    Sample outputSample;
};

#endif /* defined(__APAudioEngine__APAudioDecimatorModule__) */
