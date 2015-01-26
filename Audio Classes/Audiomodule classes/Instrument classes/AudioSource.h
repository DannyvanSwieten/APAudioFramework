//
//  AudioSource.h
//  SmartSampler
//
//  Created by Danny van Swieten on 1/10/15.
//
//

class APAudioSource
{
public:
    APAudioSource();
    virtual ~APAudioSource();
    virtual float play() = 0;
private:
    
};