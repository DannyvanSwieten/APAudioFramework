//
//  TestAudioProcessor.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__TestAudioProcessor__
#define __GUI__TestAudioProcessor__

#include "AudioProcessor.h"
#include <cstdlib>

class TestAudioProcessor: public AudioProcessor
{
public:
    
    TestAudioProcessor();
    ~TestAudioProcessor();
    
    void render(float* input, float* output, unsigned long numSamples)override final;
    
private:
};

#endif /* defined(__GUI__TestAudioProcessor__) */
