//
//  SamplerVoice.h
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#ifndef __FuChair__SamplerVoice__
#define __FuChair__SamplerVoice__

#include "AudioFile.h"

class SamplerVoice
{
public:
    SamplerVoice();
    
    void play(bool repeat);
    void stop();
    bool isPlaying();
    float tick();
    void setFileToPlay(AudioFile* fileToPlay);
    AudioFile* getPlayingFile(){return _fileToPlay;};
    void setSpeed(float speed);
    void setAmplitude(float amp);
    void setNote(int note);
    void setPosition(){_position = 0;};
    int getNote();
    
private:
    
    int _note = 0;
    float _amplitude = 1;
    bool _isPlaying = 0;
    float _speed = 1;
    float _frac = 0;
    int _floorIndex = 0;
    int _nextFloorIndex = 0;
    float _position = 0;
    bool _repeat = 0;
    AudioFile* _fileToPlay;
};


#endif /* defined(__FuChair__SamplerVoice__) */
