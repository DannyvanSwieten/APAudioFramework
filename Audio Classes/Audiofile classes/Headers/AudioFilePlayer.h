//
//  APAudioStreamPlayer.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef FuChair_APAudioStreamPlayer_h
#define FuChair_APAudioStreamPlayer_h

#include "AudioSource.h"
#include "AudioFile.h"

class AudioFilePlayer: public AudioSource
{
public:
    
    AudioFilePlayer();
    ~AudioFilePlayer();
    
    float play() ;
    void stop();
    void setPlay();
    void setFile(AudioFile* file);
    void setSampleRate(float sr);
    void setSpeed(float speed);
    
private:
    
    AudioFile* _file = nullptr;
    float _sampleRate = 0;
    float _position = 0;
    float _speed = 1.0;
    float _frac = 0;
    int _index = 0;
    int _nextIndex = 0;
};

#endif
