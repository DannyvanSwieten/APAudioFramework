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
}

void APAudioFilePlayer::setPlay()
{
    _playing = true;
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
        return _file->getAudioChannel(0)[_position++];
    }
    else
        return 0;
}