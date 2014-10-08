//
//  SamplerVoice.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef __FuChair__SamplerVoice__
#define __FuChair__SamplerVoice__

#include "APAudioFile.h"

class APSamplerVoice
{
public:
    APSamplerVoice();
    
    void play();
    bool isPlaying();
    float tick();
    void setFileToPlay(APAudioFile* fileToPlay);
    
private:
    
    bool _isPlaying = 0;
    float _speed = 0.5;
    float _frac = 0;
    int _floorIndex = 0;
    int _nextFloorIndex = 0;
    float _position = 0;
    APAudioFile* _fileToPlay;
};

#endif /* defined(__FuChair__SamplerVoice__) */
