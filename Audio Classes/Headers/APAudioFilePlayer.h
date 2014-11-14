//
//  APAudioStreamPlayer.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef FuChair_APAudioStreamPlayer_h
#define FuChair_APAudioStreamPlayer_h

#include "APAudioFile.h"

class APAudioFilePlayer
{
public:
    
    APAudioFilePlayer();
    ~APAudioFilePlayer();
    
    float play();
    void setPlay();
    void setFile(APAudioFile* file);
    void setSampleRate(float sr);
    void setSpeed(float speed);
private:
    
    APAudioFile* _file = nullptr;
    float _sampleRate = 0;
    float _position = 0;
    float _speed = 0;
    float _frac = 0;
    int _index = 0;
    int _nextIndex = 0;
    bool _playing = 0;
};

#endif
