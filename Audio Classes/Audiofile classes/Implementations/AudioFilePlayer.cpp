//
//  AudioFilePlayer.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "AudioFilePlayer.h"

AudioFilePlayer::AudioFilePlayer()
{
    
}

AudioFilePlayer::~AudioFilePlayer()
{
    
}

void AudioFilePlayer::setFile(AudioFile *file)
{
    _file = file;
    _speed = _file->getSampleRate() / _sampleRate;
}

void AudioFilePlayer::setSpeed(float speed)
{
    _speed = speed;
}

void AudioFilePlayer::setSampleRate(float sr)
{
    _sampleRate = sr;
    
    if(_file)
        _speed = _file->getSampleRate() / _sampleRate;
}

void AudioFilePlayer::stop()
{
    _position = 0;
    _index = 0;
    _nextIndex = 0;
    _frac = 0;
}

float AudioFilePlayer::play()
{
        if (_position + 1 > _file->getNumSamples())
        {
            stop();
            return 0;
        }
        
        _position += _speed;
        _index = (int)_position;
        _nextIndex = _index + 1;
        if(_nextIndex > _file->getNumChannels())
            _nextIndex = 0;
    
        _frac = _position - _index;
        
        return _file->getAudioChannel(0)[_index] + (_frac * (_file->getAudioChannel(0)[_index] - _file->getAudioChannel(0)[_nextIndex]));
}