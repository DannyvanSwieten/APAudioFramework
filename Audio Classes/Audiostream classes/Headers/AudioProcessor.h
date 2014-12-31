//
//  AudioProcessor.h
//  GUI
//
//  Created by Danny van Swieten on 10/28/14.
//
//

#ifndef __GUI__AudioProcessor__
#define __GUI__AudioProcessor__

class AudioProcessor
{
public:
    virtual ~AudioProcessor() = 0;
    
    virtual void render(float** input, float** output, unsigned long numSamples) = 0;
private:
    
};

#endif /* defined(__GUI__AudioProcessor__) */
