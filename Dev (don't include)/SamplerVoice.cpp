//
//  SamplerVoice.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "SamplerVoice.h"

SamplerVoice::SamplerVoice()
{
    
}

void SamplerVoice::play(bool repeat)
{
    _isPlaying = true;
    _repeat = repeat;
}

void SamplerVoice::stop()
{
    _isPlaying = false;
    _repeat = false;
    _frac = 0.0;
    _floorIndex = 0;
    _nextFloorIndex = 0;
}

bool SamplerVoice::isPlaying()
{
    return _isPlaying;
}

void SamplerVoice::setFileToPlay(AudioFile *fileToPlay)
{
    _fileToPlay = fileToPlay;
}

void SamplerVoice::setSpeed(float speed)
{
    _speed = speed;
}

void SamplerVoice::setAmplitude(float amp)
{
    _amplitude = amp;
}

void SamplerVoice::setNote(int note)
{
    _note = note;
}

int SamplerVoice::getNote()
{
    return _note;
}

float SamplerVoice::tick()
{
    if(_position > _fileToPlay->getNumSamples() && _repeat)
        _position -= _fileToPlay->getNumSamples();
    
    if(_position > _fileToPlay->getNumSamples() && !_repeat)
    {
        _position = 0;
        _isPlaying = false;
        return 0;
    }
    
    if(_position < 0)
        _position += _fileToPlay->getNumSamples();
    
    _floorIndex = (int)_position;
    _nextFloorIndex = _floorIndex + 1;
    _frac = _position - _floorIndex;
    
    _position += _speed;
    
    return (((1 - _frac) * _fileToPlay->getAudioChannel(0)[_floorIndex]) + (_frac * _fileToPlay->getAudioChannel(0)[_nextFloorIndex])) * _amplitude;
}

