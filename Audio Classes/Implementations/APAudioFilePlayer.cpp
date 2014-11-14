//
//  APAudioFilePlayer.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APAudioFilePlayer.h"

APAudioFilePlayer::APAudioFilePlayer()
{
    
}

APAudioFilePlayer::~APAudioFilePlayer()
{
    
}

void APAudioFilePlayer::setFile(APAudioFile *file)
{
    _file = file;
    _speed = _file->getSampleRate() / _sampleRate;
}

void APAudioFilePlayer::setPlay()
{
    _playing = true;
}

void APAudioFilePlayer::setSampleRate(float sr)
{
    _sampleRate = sr;
    
    if(_file)
        _speed = _file->getSampleRate() / _sampleRate;
}

float APAudioFilePlayer::play()
{
    if(_playing)
    {
        if (_position + 1 > _file->getNumSamples())
        {
            _position = 0;
            _playing = false;
            return 0;
        }
        
        _position += _speed;
        _index = (int)_position;
        _nextIndex = _index + 1;
        _frac = _position - _index;
        
        return _file->getAudioChannel(0)[_index] + (_frac * (_file->getAudioChannel(0)[_index] - _file->getAudioChannel(0)[_nextIndex]));
    }
    else
        return 0;
}