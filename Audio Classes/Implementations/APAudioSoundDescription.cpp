//
//  APAudioSoundDescription.cpp
//  FuChair
//
//  Created by Danny van Swieten on 10/7/14.
//
//

#include "APAudioSoundDescription.h"

APAudioSoundDescription::APAudioSoundDescription()
{
    
}

std::string APAudioSoundDescription::getID()
{
    return _ID;
}

void APAudioSoundDescription::setID(std::string ID)
{
    _ID = ID;
}

void APAudioSoundDescription::setChannelToListenTo(int channel)
{
    _channelToListenTo = channel;
}

void APAudioSoundDescription::setNoteToListenTo(int note)
{
    _noteToListenTo = note;
}

bool APAudioSoundDescription::listensToChannel(int channel)
{
    if(channel == _channelToListenTo)
        return true;
    else
        return false;
}

bool APAudioSoundDescription::listensToNote(int note)
{
    if(note == _noteToListenTo)
        return true;
    else
        return false;
}