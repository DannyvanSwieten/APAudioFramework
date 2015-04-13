//
//  AudioSource.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/10/15.
//
//

class AudioSource
{
public:
    AudioSource();
    virtual ~AudioSource();
    virtual float play() = 0;
private:
    
};