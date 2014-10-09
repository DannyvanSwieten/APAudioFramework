//
//  SamplerVoice.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APAudioSamplerVoice.h"

APAudioSamplerVoice::APAudioSamplerVoice()
{
    
}

void APAudioSamplerVoice::play(bool repeat)
{
    _isPlaying = true;
    _repeat = repeat;
}

bool APAudioSamplerVoice::isPlaying()
{
    return _isPlaying;
}

void APAudioSamplerVoice::setFileToPlay(APAudioFile *fileToPlay)
{
    _fileToPlay = fileToPlay;
}

void APAudioSamplerVoice::setSpeed(float speed)
{
    _speed = speed;
}

void APAudioSamplerVoice::setAmplitude(float amp)
{
    _amplitude = amp;
}

void APAudioSamplerVoice::setNote(int note)
{
    _note = note;
}

int APAudioSamplerVoice::getNote()
{
    return _note;
}

float APAudioSamplerVoice::tick()
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
