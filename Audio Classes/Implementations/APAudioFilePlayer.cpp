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

float APAudioFilePlayer::play(APAudioFile *file, int channel, float speed)
{
    if (channel > file->getNumChannels())
        return 0;
    else
        return file->getAudioChannel(channel)[_position++];
}