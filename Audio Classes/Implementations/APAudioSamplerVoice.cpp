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

void APAudioSamplerVoice::play()
{
    _isPlaying = true;
}

bool APAudioSamplerVoice::isPlaying()
{
    return _isPlaying;
}

void APAudioSamplerVoice::setFileToPlay(APAudioFile *fileToPlay)
{
    _fileToPlay = fileToPlay;
}

float APAudioSamplerVoice::tick()
{
    if(_position > _fileToPlay->getNumSamples())
        _position -= _fileToPlay->getNumSamples();
    
    _floorIndex = (int)_position;
    _nextFloorIndex = _floorIndex + 1;
    _frac = _position - _floorIndex;
    
    _position += _speed;
    
    return ((1 - _frac) * _fileToPlay->getAudioChannel(0)[_floorIndex]) + (_frac * _fileToPlay->getAudioChannel(0)[_nextFloorIndex]);
}
